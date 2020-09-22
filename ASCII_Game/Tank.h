#pragma once

#include <vector>

#include "scene/Entity.h"
#include "input/Gamepad.h"
#include "Textures.h"

class Tank : public Entity
{
public:
    ENTITY_TYPE(Tank);

    Gamepad* gamepad;
    float offset;

    Tank(const WORD& attributes, Gamepad* gamepad, float offset)
        : Entity(TEX_TANK_BODY, attributes, 0b10000000, 0b11000000, 5, 5), gamepad(gamepad), offset(offset) {
    }

    void OnInit() override;
    void OnUpdate() override;
    void OnCollision(Entity* other) override;
};

