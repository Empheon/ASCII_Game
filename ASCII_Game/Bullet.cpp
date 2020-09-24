#include "Bullet.h"

void Bullet::OnInit() {
    bouncesLeft = MAX_BOUNCES;
    velocity = Vector2(cos(directionAngle) * speed, sin(directionAngle) * speed);
}

void Bullet::OnUpdate()
{
    Move(velocity);
    if (position.x < 0 || position.x > parent->parent->width
        || position.y < 0 || position.y > parent->parent->height) {
        Destroy();
    }
}

void Bullet::OnDraw(Renderer* renderer)
{
    renderer->DrawChar(prevPosition.x, prevPosition.y, L'\u25cb', 0x0e, depth);
}

void Bullet::OnCollision(Entity* other, const CollisionData* data)
{
    if (other->tag == ownerTag) {
        return;
    } else if (other->GetType() == "Wall" && bouncesLeft > 0) {

        if (data->direction == CollisionData::Direction::HOR) {
            position.y = prevPosition.y;
            velocity.y *= -1.0f;
        }
        else if (data->direction == CollisionData::Direction::VERT) {
            position.x = prevPosition.x;
            velocity.x *= -1.0f;
        }

       --bouncesLeft;
       if (bouncesLeft < MAX_BOUNCES) {
           ownerTag = "NO_OWNER";
       }
    } else {
        Destroy();
    }
   
}
