#pragma once

#include <vector>
#include <algorithm>

#include "scene/Entity.h"
#include "input/Gamepad.h"
#include "Textures.h"

#include "Bullet.h"

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

    Bullet bullets[5];
    bool canShoot = true;

    float cursorAngle = -3.14f / 2;

    Tank(const WORD& attributes, Gamepad* gamepad, float offset)
        : Entity(TEX_TANK_BODY, attributes, 0b10000000, 0b11000000, 5, 5), gamepad(gamepad), offset(offset), color(attributes) {
        for (int i = 0; i < 5; i++) {
            bullets[i] = Bullet(0, 0);
        }
    }

    void OnInit() override;
    void OnUpdate() override;
    void OnDraw(Renderer* renderer) override;
    void OnCollision(Entity* other) override;
};

