#pragma once

#include <Windows.h>

#include <scene/Entity.h>

#include "Textures.h"

#define MINE_MAX_LIFETIME 8.0
#define MINE_SLOW_BLINK_SPEED 120
#define MINE_FAST_BLINK_SPEED 10
#define MINE_EXPLOSION_DURATION 0.4
#define MINE_EXPLOSION_RANGE 8

#define LAYER_PLAYERS 7
#define LAYER_EXPLOSIONS 4
#define LAYER_BULLETS 5

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
};

