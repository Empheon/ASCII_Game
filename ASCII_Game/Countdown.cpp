#include "Countdown.h"

void Countdown::OnInit() {
	ticksPerState = TIME_PER_STATE * parent->parent->targetFPS;
}

void Countdown::OnUpdate() {
	stateTime++;
	if (stateTime > ticksPerState) {
		stateTime = 0;
		state++;
		
		if (state == STATE_COUNT) {
			((GameScene*)parent)->StartGame();
			Destroy(true);
		}
	}
}

void Countdown::OnDraw(Renderer* renderer) {
	float xPos = ((float)stateTime / (float)ticksPerState);
	float trueX = easeOutIn(xPos, 0, 1, 1.0) * parent->parent->width;
	Texture tex = TEX_START_COUNTDOWN[state % STATE_COUNT];
	parent->parent->renderer->DrawTexture(trueX - tex.GetWidth() / 2.0f, parent->parent->height / 2 - 3, tex, COUNTDOWN_COLORS[state % 4], depth);
}

float Countdown::easeOut(float t, float b, float c, float d)
{
	return (t == d) ? b + c : c * (-pow(2, -10 * t / d) + 1) + b;
}

float Countdown::easeIn(float t, float b, float c, float d)
{
	return (t == 0) ? b : c * pow(2, 10 * (t / d - 1)) + b;
}

float Countdown::easeOutIn(float t, float b, float c, float d)
{
	if (t < d / 2)
		return easeOut(t * 2, b, c / 2, d);

	return easeIn((t * 2) - d, b + c / 2, c / 2, d);
}