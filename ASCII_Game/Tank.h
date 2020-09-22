#pragma once

#include <vector>

#include "scene/Entity.h"
#include "input/Gamepad.h"
#include "Textures.h"

class Tank : public Entity
{
public:
    Gamepad* gamepad;

    Tank(const WORD& attributes, Gamepad* gamepad)
        : Entity(TEX_TANK_BODY, attributes, 0b10000000, 0b10000000, 5, 5), gamepad(gamepad) {
    }

    void OnInit() override;
    void OnUpdate() override;
    void OnCollision(Entity* other) override;
};

