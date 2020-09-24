#include "Particle.h"

void Particle::Update()
{
	lifeLeft--;
	lifeTime++;
	if (lifeLeft <= 0)
		active = false;

	position += velocity;
	zPosition -= zVelocity;
	if (zPosition < 0) {
		zPosition = 0;
		zVelocity = -zVelocity * bounceFactor;
	}

	zVelocity += gravity;

	velocity += acceleration;
	zVelocity += gravity;

	velocity *= friction;
}

void Particle::Draw(Renderer* renderer)
{
	renderer->DrawChar(position.x, position.y - zPosition, L'O', 0x0a, zIndex);
}
