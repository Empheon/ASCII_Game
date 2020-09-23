#pragma once

#include <vector>

#include "scene/Entity.h"
#include "input/Gamepad.h"
#include "Textures.h"

class Tank : public Entity
{
public:
    ENTITY_TYPE(Tank);

    Texture cursorTexture = TEX_TANK_CURSOR;

    Gamepad* gamepad;
    const float speed = 0.5f;
    const float cursorDistance = 12.0f;
    float offset;
    WORD color;

    Vector2 cursor;

    Tank(const WORD& attributes, Gamepad* gamepad, float offset)
        : Entity(TEX_TANK_BODY, attributes, 0b10000000, 0b11000000, 5, 5), gamepad(gamepad), offset(offset), color(attributes) {
    }

    void OnInit() override;
    void OnUpdate() override;
    void OnDraw(Renderer* renderer) override;
    void OnCollision(Entity* other, const CollisionData* data) override;
};

