#pragma once

#include <iostream>
#include <Windows.h>
#include <Xinput.h>

#define JOYSTICK_MAX_VALUE 32767

class Gamepad
{
private:
	int id;
	XINPUT_STATE state;
	float leftX, leftY, rightX, rightY, leftTrigger, rightTrigger;

public:
	Gamepad(int id, XINPUT_STATE state);
	void Update();
	int GetPort();
	XINPUT_GAMEPAD* GetState();

	float GetStickLX();
	float GetStickLY();

	float GetStickRX();
	float GetStickRY();
};

