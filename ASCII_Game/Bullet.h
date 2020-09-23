#pragma once
#include "scene/Entity.h"
#include "Textures.h"

#include <iostream>

#define MAX_BOUNCES 1

class Bullet : public Entity
{
public:
    ENTITY_TYPE(Bullet);

    float directionAngle = 0;
    float speed;
    int bouncesLeft;
    Vector2 velocity;
    std::string ownerTag;

    Bullet(float x, float y)
        : Entity(TEX_BULLET, 0x0E, 0b00100000, 0b11100000, 1, 1) {
        this->position.x = x;
        this->position.y = y;
        depth = -10;
    }

    Bullet() {};

    void OnInit() override;
    void OnUpdate() override;
    void OnDraw(Renderer* renderer) override;
    void OnCollision(Entity* other, const CollisionData* data) override;
};

