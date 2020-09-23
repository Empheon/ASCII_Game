#pragma once

#define _USE_MATH_DEFINES

#include <vector>
#include <algorithm>
#include <cmath>

#include "scene/Entity.h"
#include "input/Gamepad.h"
#include "Textures.h"

class Tank : public Entity
{
public:
    ENTITY_TYPE(Tank);

    Tank(const WORD& attributes, Gamepad* gamepad, float offset)
        : Entity(TEX_TANK_BODY, attributes, 0b10000000, 0b11000000, 5, 5), gamepad(gamepad), offset(offset), color(attributes) {
    }

private:
    Texture cursorTexture = TEX_TANK_CURSOR;
    WORD color;
    const Vector2 cannonOffset = Vector2(2, 2);

    Gamepad* gamepad;
    const float speed = 0.5f;
    const float cursorDistance = 12.0f;
    float offset;

    Vector2 cursor;
    float cursorAngle = 0.0f;
    int approxAngle = 0;

    void DrawCannon(Renderer* renderer) const;

    void OnInit() override;
    void OnUpdate() override;
    void OnDraw(Renderer* renderer) override;
    void OnCollision(Entity* other, const CollisionData* data) override;
};

