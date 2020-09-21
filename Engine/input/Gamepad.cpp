#include "Gamepad.h"

Gamepad::Gamepad(int id, XINPUT_STATE state)
: id(id), state(state) {

}

void Gamepad::Update() {
	DWORD result;
	result = XInputGetState(id, &state);

	float lxNorm = fmaxf(-1.0, (float) state.Gamepad.sThumbLX / JOYSTICK_MAX_VALUE);
	float lyNorm = fmaxf(-1.0, (float) state.Gamepad.sThumbLY / JOYSTICK_MAX_VALUE);

	leftX = (abs(lxNorm) < 0.2f ? 0 : (abs(lxNorm) - 0.2f) * (lxNorm / abs(lxNorm)));
	leftY = (abs(lyNorm) < 0.2f ? 0 : (abs(lyNorm) - 0.2f) * (lyNorm / abs(lyNorm)));

	leftX *= 1 / (1 - 0.2);
	leftY *= 1 / (1 - 0.2);

	float rxNorm = fmaxf(-1.0, (float)state.Gamepad.sThumbRX / JOYSTICK_MAX_VALUE);
	float ryNorm = fmaxf(-1.0, (float)state.Gamepad.sThumbRY / JOYSTICK_MAX_VALUE);

	rightX = (abs(rxNorm) < 0.2f ? 0 : (abs(rxNorm) - 0.2f) * (rxNorm / abs(rxNorm)));
	rightY = (abs(ryNorm) < 0.2f ? 0 : (abs(ryNorm) - 0.2f) * (ryNorm / abs(ryNorm)));

	rightX *= 1 / (1 - 0.2);
	rightY *= 1 / (1 - 0.2);
}

int Gamepad::GetPort() {
	return id;
}

XINPUT_GAMEPAD* Gamepad::GetState()
{
	return &state.Gamepad;
}

float Gamepad::GetStickLX()
{
	return leftX;
}

float Gamepad::GetStickLY()
{
	return leftY;
}

float Gamepad::GetStickRX()
{
	return rightX;
}

float Gamepad::GetStickRY()
{
	return rightY;
}

