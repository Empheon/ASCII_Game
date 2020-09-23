#include "Bullet.h"

void Bullet::OnUpdate()
{
    Move(cos(directionAngle) * speed, sin(directionAngle) * speed);
}

void Bullet::OnDraw(Renderer* renderer)
{
    //renderer->DrawSprite(position.x, position.y, texture, color);
}

void Bullet::OnCollision(Entity* other, const CollisionData* data)
{
    if (other->tag == ownerTag) {
        return;
    }
    Destroy();
}
