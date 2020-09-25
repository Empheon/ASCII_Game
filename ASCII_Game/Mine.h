#pragma once

#include <Windows.h>

#include <scene/Entity.h>

#include "Textures.h"

#define MINE_MAX_LIFETIME 4.0
#define MINE_SLOW_BLINK_SPEED 60
#define MINE_FAST_BLINK_SPEED 5
#define MINE_EXPLOSION_DURATION 0.4
#define MINE_EXPLOSION_RANGE 10

#define LAYER_PLAYERS 7
#define LAYER_EXPLOSIONS 4
#define LAYER_BULLETS 5

const ParticleInfo PART_MINE_SMOKE_BASE {
	0.1f, 0.0f, {0.0f, 0.0f},
	0.0f, 0.0f, -0.005f, 0.0f,
	0.0f,
	0x0f, 0, 60,
	30
};

const ParticleInfo PART_MINE_SPARKLE_BASE {
	0.5f, 0.0f, {0.0f, 0.0f},
	0.0f, -2.0f, 0.08f, 0.8f,
	0.92f,
	0x0e, L'X', 61,
	20
};

class Mine : public Entity
{
public:
	ENTITY_TYPE(Mine);

	std::string ownerTag;
	WORD color;

	Mine() 
		: Entity(0b00000000, 0b00110000, 1, 1) {
	}

	void OnInit() override;
	void OnUpdate() override;
	void OnDraw(Renderer* renderer) override;
	void OnCollision(Entity* other, const CollisionData* data) override;

private:
	int lifeTime;
	int blinkSpeed;
	bool exploaded;


	void SetExplosionCollider();
	void ResetCollider();
	void Kaboom();

	void SpawnExplosionParticles();

	static ParticleInfo CreateSmokeParticle();
	static ParticleInfo CreateSparkleParticle();
};

