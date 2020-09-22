#pragma once
#include <Windows.h>
#include <iostream>
#include "render/Renderer.h"
#include <sstream>

#include "Timer.h"
#include "input/InputManager.h"

class Scene;

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

    virtual void OnInit() {};
    virtual void OnUpdate() {};
    virtual void OnPreDraw() {};
    virtual void OnPostDraw() {};

    void Run();
    void Stop();

    void LoadScene(Scene* scene);

protected:
    Scene* currentScene;

private:
	bool running;
	Timer loopTimer;
	float targetFPS;
    COORD dwBufferSize;
    COORD dwBufferCoord;
    SMALL_RECT rcRegion;

    void UpdateInputs();
    void Update();
    void Draw();
};

