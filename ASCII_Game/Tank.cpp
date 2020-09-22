#include "Tank.h"

void Tank::Update()
{
    Move(1, 0);
}

void Tank::OnCollision(Entity* other)
{
}
