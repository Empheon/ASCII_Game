#pragma once
#include "scene/Entity.h"
#include "Textures.h"

#include <iostream>

#define MAX_BOUNCES 1

const ParticleInfo PART_BULLET_SMOKE_BASE {
    0.4f, 0.0f, {0.0f, 0.0f},
    0.0f, 0.0f, -0.01f, 0.0f,
    0.6f,
    0x0f, 0, -11,
    10
};

const ParticleInfo PART_BULLET_SPARKLE_BASE {
    2.0f, 0.0f, {0.0f, 0.0f},
    0.0f, -1.0f, 0.05f, 0.0f,
    1.0f,
    0x0e, L'X', -9,
    5
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
    
private:
    void SpawnImpactParticles();

    static ParticleInfo CreateSmokeParticle(const float bulletDir);
    static ParticleInfo CreateSparkleParticle();
};

