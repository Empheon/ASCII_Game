#pragma once

#include <scene/Entity.h>

#include "scenes/GameScene.h"
#include "Textures.h"

#define TIME_PER_STATE 1.0
#define STATE_COUNT 4

const WORD COUNTDOWN_COLORS[] = { 0x0c, 0x0e, 0x0a, 0x0f };

class Countdown : public Entity
{
public:
	ENTITY_TYPE(Countdown);

	Countdown()
		: Entity(0b00000000, 0b00000000, 0, 0) {
		depth = 100;
	}

	void OnInit() override;
	void OnUpdate() override;
	void OnDraw(Renderer* renderer) override;

private:
	int ticksPerState;
	int state;
	int stateTime;

	static float easeOut(float t, float b, float c, float d);
	static float easeIn(float t, float b, float c, float d);
	static float easeOutIn(float t, float b, float c, float d);
};

