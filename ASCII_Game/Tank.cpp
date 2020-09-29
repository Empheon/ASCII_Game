#include "Tank.h"
#include "scenes/GameScene.h"

void Tank::OnInit() {
    cursor.x = position.x;
    cursor.y = position.y - 4.0f;
    SetTag("tank" + gamepad->GetId());
}

void Tank::OnUpdate() {
    float sx = gamepad->GetStickLX();
    float sy = -gamepad->GetStickLY();

    Move(sx * speed, sy * speed);

    sx = gamepad->GetStickRX();
    sy = -gamepad->GetStickRY();
    Vector2 stickR = Vector2(sx, sy);

    // Update cursor if not too close from the origin
    if (stickR.Length() > 0.2f) {
        cursorAngle = stickR.Angle();
    }

    cursor.x = position.x + cos(cursorAngle) * cursorDistance;
    cursor.y = position.y + sin(cursorAngle) * cursorDistance;

    if (gamepad->IsButtonDown(XINPUT_GAMEPAD_B)) {
        depth--;
        if (depth < -50) depth = 50;
    } else if (gamepad->IsButtonDown(XINPUT_GAMEPAD_A)) {
        depth++;
        if (depth > 50) depth = -50;
    }

    if (gamepad->IsButtonDown(XINPUT_GAMEPAD_RIGHT_SHOULDER)) {
        if (canShoot) {
            for (Bullet& b : bullets) {
                if (!b.IsValidInstance()) {
                    canShoot = false;
                    b.directionAngle = cursorAngle;
                    b.speed = 1.0f;
                    b.ownerTag = tag;
                    parent->Instantiate(&b, position + cannonOffset);
                    break;
                }
            }
        }
    }
    else {
        canShoot = true;
    }

    if (gamepad->IsButtonDown(XINPUT_GAMEPAD_LEFT_SHOULDER)) {
        if (canPlaceMine) {
            for (Mine& m : mines) {
                if (!m.IsValidInstance()) {
                    canPlaceMine = false;
                    m.ownerTag = tag;
                    m.color = attributes;
                    parent->Instantiate(&m, position + cannonOffset);
                    break;
                }
            }
        }
    }
    else {
        canPlaceMine = true;
    }
    
    approxAngle = round((cursorAngle + M_PI) / M_PI * 4.0f);

    invincibilityDelay = max(0, invincibilityDelay-1);
    visible = (invincibilityDelay % 4 < 2);
}

void Tank::OnDraw(Renderer* renderer) {

    std::wstringstream ss;
    ss << "cannon: " << cursorAngle << " a: " << approxAngle;

    DrawCannon(renderer);

    renderer->DrawTexture(cursor.x, cursor.y, cursorTexture, color, 100);
    //renderer->DrawString(position.x, position.y - 2, ss.str(), color, 99);

    std::wstringstream hpStr;
    for (int i = 0; i < hitPoints; i++) {
        hpStr << L"\u2590";
    }

    WORD hpColor = 0x0A;
    if (hitPoints <= 1) {
        hpColor = 0x0C;
    }
    else if (hitPoints <= 3) {
        hpColor = 0x0E;
    }

    renderer->DrawString(position.x, position.y - 2, hpStr.str(), hpColor, 99);
      // renderer->DrawCircle(position.x, position.y, 10, L'\u2666', 0x0f, 127);
};

void Tank::OnCollision(Entity* other, const CollisionData* data) {
    std::wstringstream ss;

    if (other->GetType() == "Wall" || other->GetType() == "Tank") {
        if (data->direction == CollisionData::Direction::HOR) {
            position.y = prevPosition.y;
        } else if (data->direction == CollisionData::Direction::VERT) {
            position.x = prevPosition.x;
        }
        return;
    }

    if (other->GetType() == "Bullet" && ((Bullet*) other)->ownerTag != tag) {
        Hit();
        parent->parent->renderer->DoScreenShake(1.5f);
        return;
    }

    if (other->GetType() == "Mine") {
        Hit();
        parent->parent->renderer->DoScreenShake(1.8f);
    }
}

void Tank::DrawCannon(Renderer* renderer) const {
    renderer->DrawTexture(position.x - 1, position.y - 1, TEX_TANK_CANNON[approxAngle % 8], color, depth);
}

void Tank::Hit() {
    if (invincibilityDelay > 0)
        return;
    
    parent->parent->renderer->FreezeFrame(5);
    hitPoints--;
    SetInvincible();
    SpawnPartParticles();

    if (hitPoints <= 0) {
        parent->parent->renderer->FreezeFrame(12);
        Destroy();
        ((GameScene*)parent)->DestroyTank(this);
    }
}

void Tank::SetInvincible() {
    invincibilityDelay = INVINCIBILITY_TIME * parent->parent->targetFPS;
}

void Tank::SpawnPartParticles()
{
    for (int i = 0; i < 10; ++i) {
        ParticleInfo info = Tank::CreatePartParticle(*this);
        parent->parent->particles.Emit(info, position);
    }
}

ParticleInfo Tank::CreatePartParticle(const Tank& tank)
{
    ParticleInfo part = PART_TANK_PART_BASE;
    part.direction = RandFloatRange(0.0f, 2.0f * M_PI);
    part.velocity += RandFloatRange(-0.2f, 0.4f);
    part.color = tank.attributes;
    part.zVelocity *= RandFloatRange(0.8f, 1.2f);
    part.character = PART_TANK_PARTS[rand() % 8];
    part.lifeTime += rand() % 60;
    return part;
}
