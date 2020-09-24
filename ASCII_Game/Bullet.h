#pragma once
#include "scene/Entity.h"
#include "Textures.h"

#include <iostream>

#define MAX_BOUNCES 1

const std::vector<wchar_t> PART_CHARS_SHRINKING_CIRCLE = { L'O', L'\u25cb', L'\u00b0', L'\u2219' };
const ParticleInfo PART_BULLET_BASE {
    0.4f, 0.0f, {0.0f, 0.0f},
    0.0f, 0.0f, -0.01f, 0.0f,
    0.6f,
    {}, {}, -11,
    10
};


class Bullet : public Entity
{
public:
    ENTITY_TYPE(Bullet);

    float directionAngle = 0;
    float speed;
    int bouncesLeft;
    Vector2 velocity;
    std::string ownerTag;

    Bullet()
        : Entity(TEX_BULLET, 0x0e, 0b00100000, 0b11110000, 1, 1) {
        depth = -10;
    }

    
    void OnInit() override;
    void OnUpdate() override;
    void OnDraw(Renderer* renderer);
    void OnCollision(Entity* other, const CollisionData* data) override;

    static ParticleInfo CreateBulletParticle(const float bulletDir);
};

