#include "Tank.h"

void Tank::OnInit() {
    Move((parent->parent->width / 2) - 2.5f + offset, (parent->parent->height / 2) - 2.5f);

    cursor.x = position.x;
    cursor.y = position.y - 4.0f;
    SetTag("tank");
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
}

void Tank::OnDraw(Renderer* renderer) {

    std::wstringstream ss;
    ss << "D: " << depth;

    renderer->DrawTexture(cursor.x, cursor.y, cursorTexture, color, 100);
    renderer->DrawString(position.x, position.y - 2, ss.str(), color, 99);
};

void Tank::OnCollision(Entity* other, const CollisionData* data) {
    /*Tank* t = (Tank*)other;
    std::wstringstream ss;
    ss << "[Tank] collision: " << gamepad->GetId() << " colliding " << t->gamepad->GetId() << std::endl;
    OutputDebugString(ss.str().c_str());*/
    std::wstringstream ss;

    if (other->GetType() == "Wall") {
        if (data->direction == CollisionData::Direction::HOR) {
            position.y = prevPosition.y;
        } else if (data->direction == CollisionData::Direction::VERT) {
            position.x = prevPosition.x;
        }
    }
}
