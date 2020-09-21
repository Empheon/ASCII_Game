#pragma once

#include <Windows.h>
#include <Xinput.h>

class InputManager
{
public:
	InputManager();
	void Init();
	void Update();
	bool IsButtonDown(int button);

private:
	
};