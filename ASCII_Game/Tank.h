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

#define INVINCIBILITY_TIME 1.0

const std::vector<wchar_t> PART_TANK_PARTS = { L'/', L'\u2564', L'\u2563', L'\u263c', L'\u2551', L'\u2550', L'\\', L'\u0398' };
const ParticleInfo PART_TANK_PART_BASE {
    0.5f, 0.0f, {0.0f, 0.0f},
    0.0f, -1.5f, 0.08f, 0.9f,
    0.96f,
    0x0f, L'#', -1,
    60 * 10
};

class Tank : public Entity
{
public:
    ENTITY_TYPE(Tank);

    Tank(const WORD& attributes, Gamepad* gamepad)
        : Entity(TEX_TANK_BODY, attributes, 0b10000000, 0b11110000, 5, 5), gamepad(gamepad), color(attributes) {
    }
    Gamepad* gamepad;
    WORD color;

private:
    Texture cursorTexture = TEX_TANK_CURSOR;
    const Vector2 cannonOffset = Vector2(2, 2);

    const float speed = 0.5f;
    const float cursorDistance = 20.0f;

    Vector2 cursor;
    int approxAngle = 0;

    Bullet bullets[5];
    Mine mines[3];
    bool canShoot = true;
    bool canPlaceMine = true;

    float cursorAngle = -3.14f / 2;

    int hitPoints = 5;
    int invincibilityDelay = 0;
    
    void DrawCannon(Renderer* renderer) const;

    void OnInit() override;
    void OnUpdate() override;
    void OnDraw(Renderer* renderer) override;
    void OnCollision(Entity* other, const CollisionData* data) override;

    void Hit();
    void SetInvincible();

    void SpawnPartParticles();

    static ParticleInfo CreatePartParticle(const Tank& tank);
};

