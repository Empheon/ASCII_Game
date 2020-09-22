#pragma once

#include "scene/Entity.h"

class Wall : public Entity
{
public:
    ENTITY_TYPE(Wall);

    Wall(float x, float y, float w, float h)
        : Entity(0b01000000, 0b00000000, w, h) {
        this->position.x = x;
        this->position.y = y;
    }

    void OnDraw(Renderer* renderer) override;
};

