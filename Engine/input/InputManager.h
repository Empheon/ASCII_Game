#pragma once

#include <iostream>
#include <vector>
#include <Windows.h>
#include <Xinput.h>

#include "Gamepad.h"

#define MAX_CONNECTED_GAMEPADS 4

class InputManager
{
public:
	InputManager();
	~InputManager();
	void Update();
	bool SearchGamepads();
	Gamepad* GetGamepad(int i);
	size_t GetConnectedGamepadCount();

private:
	std::vector<Gamepad> gamepads;
};