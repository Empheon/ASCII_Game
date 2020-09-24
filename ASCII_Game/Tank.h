#pragma once

#define _USE_MATH_DEFINES

#include <vector>
#include <algorithm>
#include <cmath>

#include "scene/Entity.h"
#include "input/Gamepad.h"
#include "Textures.h"

#include "Bullet.h"
#include "Mine.h"

class Tank : public Entity
{
public:
    ENTITY_TYPE(Tank);

    Tank(const WORD& attributes, Gamepad* gamepad, float offset)
        : Entity(TEX_TANK_BODY, attributes, 0b10000000, 0b11100000, 5, 5), gamepad(gamepad), offset(offset), color(attributes) {
    }
    Gamepad* gamepad;
    WORD color;

private:
    Texture cursorTexture = TEX_TANK_CURSOR;
    const Vector2 cannonOffset = Vector2(2, 2);

    const float speed = 0.5f;
    const float cursorDistance = 30.0f;
    float offset;

    Vector2 cursor;
    int approxAngle = 0;

    Bullet bullets[5];
    Mine mines[3];
    bool canShoot = true;
    bool canPlaceMine = true;

    float cursorAngle = -3.14f / 2;

    int hitPoints = 5;
    
    void DrawCannon(Renderer* renderer) const;

    void OnInit() override;
    void OnUpdate() override;
    void OnDraw(Renderer* renderer) override;
    void OnCollision(Entity* other, const CollisionData* data) override;
};

