#pragma once

#include "ParticleInfo.h"
#include "../../Vector2.h"
#include "../../render/Renderer.h"

class ParticleEmitter;

class Particle
{
	friend class ParticleEmitter;
private:
	bool active = false;
	
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
	float zPosition;
	float zVelocity;
	float gravity;
	float bounceFactor;
	float friction;

	WORD* colors;
	wchar_t* chars;
	int8_t zIndex;

	int lifeTime;
	int lifeLeft;

	void Update();
	void Draw(Renderer* renderer);
};

