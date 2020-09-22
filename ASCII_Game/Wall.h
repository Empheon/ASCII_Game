#pragma once

#include "scene/Entity.h"

#define WALL_TOP_LEFT L'\u250c'
#define WALL_TOP_RIGHT L'\u2510'
#define WALL_BOTTOM_LEFT L'\u2558'
#define WALL_BOTTOM_RIGHT L'\u255b'
#define WALL_VER L'\u2502'
#define WALL_HOR L'\u2500'
#define WALL_BOTTOM L'\u2550'

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

