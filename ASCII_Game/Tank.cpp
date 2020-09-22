#include "Tank.h"

void Tank::OnInit() {
    posX = 5.0f;
    posY = 5.0f;
}

void Tank::OnUpdate() {
    float sx = gamepad->GetStickLX();
    float sy = -gamepad->GetStickLY();
    Move(sx, sy);
}

void Tank::OnCollision(Entity* other) {
}
