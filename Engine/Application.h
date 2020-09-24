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

    size_t GetAppTicks() const;
    void LoadScene(Scene* scene);

protected:
    Scene* currentScene;
    Scene* sceneToDelete;

private:
	bool running;
	Timer loopTimer;
	float targetFPS;
    COORD dwBufferSize;
    COORD dwBufferCoord;
    SMALL_RECT rcRegion;
    size_t appTicks; // Total number of ticks since application start

    void UpdateInputs();
    void Update();
    void Draw();
};

