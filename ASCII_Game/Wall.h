#pragma once

#include "scene/Entity.h"

class Wall : public Entity
{
public:
    Wall(float x, float y, float w, float h)
        : Entity(0b01000000, 0b00000000, w, h) {
        this->x = x;
        this->y = y;
    }

    void OnDraw(Renderer* renderer) override;
};

