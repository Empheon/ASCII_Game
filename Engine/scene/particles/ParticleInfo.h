#pragma once

#include <iostream>
#include <Windows.h>
#include "../../Vector2.h"

const wchar_t PART_CHARS_SHRINKING_CIRCLE[4] = { L'O', L'\u25cb', L'\u00b0', L'\u2219' };

struct ParticleInfo {
	float velocity;
	float direction;
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
};

const ParticleInfo PART_SMOKE {
	2.0f, 0.0f, {0.0f, 0.0f},
	0.0f, 0.0f, 0.0f, 0.0f,
	0.9f,
	nullptr, nullptr, 60,
	60
};

const ParticleInfo PART_BOUNCE {
	1.0f, 0.0f, {0.0f, 0.0f},
	0.0f, -2.0f, 0.1f, 0.8f,
	0.96f,
	nullptr, nullptr, 60,
	60*4
};