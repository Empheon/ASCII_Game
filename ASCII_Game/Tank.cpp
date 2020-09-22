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
}
