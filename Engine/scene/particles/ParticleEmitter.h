#pragma once

#include <vector>

#include "../../render/Renderer.h"
#include "ParticleInfo.h"
#include "Particle.h"

#define PART_MAX_NUMBER 128

class ParticleEmitter
{
public:
	ParticleEmitter();

	void Update();
	void Draw(Renderer* renderer);

	void Emit(const ParticleInfo& pi, const Vector2& position);
	void Clear(); // Clears all particles on the screen

private:
	std::vector<Particle> particlePool;
	unsigned int poolIndex;
};

