#include "Tank.h"

void Tank::OnInit() {
    x = 5.0f;
    y = 5.0f;
    SetTag("tank");
}

void Tank::OnUpdate() {
    float sx = gamepad->GetStickLX();
    float sy = -gamepad->GetStickLY();
    Move(sx, sy);

    if (gamepad->IsButtonDown(XINPUT_GAMEPAD_B)) {
        std::vector<Entity*> ts = parent->FindByTag("tank");
        ((Tank*)ts[0])->Destroy();
    }
}

void Tank::OnCollision(Entity* other) {
    /*Tank* t = (Tank*)other;
    std::wstringstream ss;
    ss << "[Tank] collision: " << gamepad->GetId() << " colliding " << t->gamepad->GetId() << std::endl;
    OutputDebugString(ss.str().c_str());*/
    std::wstringstream ss;
    ss << "[Tank] Wall collision !" << gamepad->GetId() << std::endl;
    OutputDebugString(ss.str().c_str());
    x = xPrev;
    y = yPrev;

}
