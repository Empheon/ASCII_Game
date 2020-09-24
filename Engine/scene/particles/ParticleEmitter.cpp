#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter() {
	particlePool.resize(PART_MAX_NUMBER);
	poolIndex = 0;
}

void ParticleEmitter::Update() {
	for (Particle& p : particlePool) {
		if (p.active)
			p.Update();
	}
}

void ParticleEmitter::Draw(Renderer* renderer) {
	for (Particle& p : particlePool) {
		if (p.active)
			p.Draw(renderer);
	}
}

void ParticleEmitter::Emit(const ParticleInfo& pi, const Vector2& position) {
	Particle& part = particlePool[poolIndex];
	part.position = position;
	part.velocity = Vector2::fromPolar(pi.velocity, pi.direction);
	part.acceleration = pi.acceleration;
	part.zPosition = pi.zPosition;
	part.zVelocity = pi.zVelocity;

	part.gravity = pi.gravity;
	part.bounceFactor = pi.bounceFactor;

	part.friction = pi.friction;

	part.lifeLeft = pi.lifeTime;
	part.active = true;

	poolIndex = --poolIndex % particlePool.size();
}
