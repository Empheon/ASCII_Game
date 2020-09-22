#pragma once
#include <Windows.h>
#include <iostream>
#include "render/Renderer.h"
#include <sstream>

#include "Timer.h"
#include "input/InputManager.h"

class Application
{
public:
    int width, height;
    HANDLE hOutput;

    Renderer* renderer;
    InputManager input;

    Application(const short width, const short height, const short fontW, const short fontH, const float targetFPS);
    ~Application();

    void RefreshFrame();

    virtual void OnUpdate(double delta) = 0;
    virtual void OnRender() = 0;

    void Run();
    void Stop();

private:
	bool running;
	Timer loopTimer;
	float targetFPS;
    COORD dwBufferSize;
    COORD dwBufferCoord;
    SMALL_RECT rcRegion;

    void UpdateInputs();
};

