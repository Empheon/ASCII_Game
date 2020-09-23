#pragma once
#include "scene/Entity.h"
#include "Textures.h"

#include <iostream>

class Bullet : public Entity
{
public:
    ENTITY_TYPE(Bullet);

    float directionAngle = 0;
    float speed;
    std::string ownerTag;

    Bullet(float x, float y)
        : Entity(TEX_BULLET, 0x0E, 0b00100000, 0b11100000, 1, 1) {
        this->position.x = x;
        this->position.y = y;
    }

    Bullet() {};

    void OnUpdate() override;
    void OnDraw(Renderer* renderer) override;
    void OnCollision(Entity* other) override;

    void Setup(const Vector2& position, float angle, float speed) {
        this->position = position;
        this->directionAngle = angle;
        this->speed = speed;
    }
};
