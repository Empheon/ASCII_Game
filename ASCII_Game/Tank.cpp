#include "Tank.h"

void Tank::OnInit() {
    Move((parent->parent->width / 2) - 2.5f + offset, (parent->parent->height / 2) - 2.5f);

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
                if (b.destroyed) {
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
    
    approxAngle = round((cursorAngle + M_PI) / M_PI * 4.0f);
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

    if (other->GetType() == "Wall") {
        if (data->direction == CollisionData::Direction::HOR) {
            position.y = prevPosition.y;
        } else if (data->direction == CollisionData::Direction::VERT) {
            position.x = prevPosition.x;
        }
    }

    if (other->GetType() == "Bullet" && ((Bullet*) other)->ownerTag != tag) {
        hitPoints--;
        parent->parent->renderer->DoScreenShake(1.5f);
    }
}

void Tank::DrawCannon(Renderer* renderer) const {
    renderer->DrawTexture(position.x - 1, position.y - 1, TEX_TANK_CANNON[approxAngle % 8], color, depth);
}