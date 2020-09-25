#pragma once

#include <vector>
#include <Windows.h>
#include "../../Random.h"
#include "../../Vector2.h"

const std::vector<wchar_t> PART_CHARS_SHRINKING_CIRCLE = { L'O', L'\u25cb', L'\u00b0', L'\u2219' };

struct ParticleInfo {
	float velocity;
	float direction;
	Vector2 acceleration;
	float zPosition;
	float zVelocity;
	float gravity;
	float bounceFactor;
	float friction;

	WORD color;
	wchar_t character;
	int8_t zIndex;

	int lifeTime;
};

const ParticleInfo PART_SMOKE_BASE {
	2.0f, 0.0f, {0.0f, 0.0f},
	0.0f, 0.0f, 0.0f, 0.0f,
	0.9f,
	0x08, 'O', 60,
	60
};

const ParticleInfo PART_BOUNCE_BASE {
	1.0f, 0.0f, {0.0f, 0.0f},
	0.0f, -2.0f, 0.1f, 0.8f,
	0.96f,
	0x08, L'0', 60,
	60*4
};