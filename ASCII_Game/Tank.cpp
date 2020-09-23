#include "Tank.h"

void Tank::OnInit() {
    position.x = (parent->parent->width / 2) - 2.5f + offset;
    position.y = (parent->parent->height / 2) - 2.5f;

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
        std::vector<Entity*> ts = parent->FindByTag("tank");
        ((Tank*)ts[0])->Destroy();
    }

    if (gamepad->IsButtonDown(XINPUT_GAMEPAD_RIGHT_SHOULDER)) {
        if (canShoot) {
            for (Bullet& b : bullets) {
                if (b.destroyed) {
                    canShoot = false;
                    b.position = Vector2(position.x + 2, position.y + 2);
                    b.directionAngle = cursorAngle;
                    b.speed = 0.5f;
                    b.ownerTag = tag;
                    parent->Instantiate(&b);

                    break;
                }
            }
        }
    }
    else {
        canShoot = true;
    }
}

void Tank::OnDraw(Renderer* renderer) {
    
    renderer->DrawSprite(cursor.x, cursor.y, cursorTexture, color);
}

void Tank::OnCollision(Entity* other) {
    /*Tank* t = (Tank*)other;
    std::wstringstream ss;
    ss << "[Tank] collision: " << gamepad->GetId() << " colliding " << t->gamepad->GetId() << std::endl;
    OutputDebugString(ss.str().c_str());*/
    std::wstringstream ss;
    ss << "[Tank] Collisition collision !" << other->GetType().c_str() << std::endl;
    OutputDebugString(ss.str().c_str());

    if (other->GetType() == "Wall") {
        position.x = prevPosition.x;
        position.y = prevPosition.y;
    }
}
