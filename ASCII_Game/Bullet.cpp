#include "Bullet.h"

void Bullet::OnInit() {
    bouncesLeft = MAX_BOUNCES;
    velocity = Vector2(cos(directionAngle) * speed, sin(directionAngle) * speed);
}

void Bullet::OnUpdate()
{
    Move(velocity);
    if (parent->parent->GetAppTicks() % 3 == 0) {
        ParticleInfo info = Bullet::CreateBulletParticle(velocity.Angle());
        parent->parent->particles.Emit(info, position);
    }

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

ParticleInfo Bullet::CreateBulletParticle(const float bulletDir) {
    ParticleInfo part = PART_BULLET_BASE;
    part.direction = bulletDir + RandFloatRange(-0.4, 0.4);
    part.color = (rand() % 2 == 0) ? 0x07 : 0x08;
    part.character = PART_CHARS_SHRINKING_CIRCLE[rand() % 4];
    return part;
}
