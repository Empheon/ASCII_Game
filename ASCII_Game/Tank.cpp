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
    cursor.x = position.x + 1.0 + sx * cursorDistance;
    cursor.y = position.y + 1.0 + sy * cursorDistance;

    if (gamepad->IsButtonDown(XINPUT_GAMEPAD_B)) {
        std::vector<Entity*> ts = parent->FindByTag("tank");
        ((Tank*)ts[0])->Destroy();
    }
}

void Tank::OnDraw(Renderer* renderer) {
    
    renderer->DrawSprite(cursor.x, cursor.y, cursorTexture, color);
}

void Tank::OnCollision(Entity* other, const CollisionData* data) {
    /*Tank* t = (Tank*)other;
    std::wstringstream ss;
    ss << "[Tank] collision: " << gamepad->GetId() << " colliding " << t->gamepad->GetId() << std::endl;
    OutputDebugString(ss.str().c_str());*/
    std::wstringstream ss;

    //if (other->GetType() == "Wall") {
        if (data->direction == CollisionData::Direction::HOR) {
            position.y = prevPosition.y;
        } else if (data->direction == CollisionData::Direction::VERT) {
            position.x = prevPosition.x;
        }
    //}
}
