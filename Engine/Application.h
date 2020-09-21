#pragma once
#include <Windows.h>
#include <iostream>
#include "Renderer.h"
#include <sstream>

#include "Timer.h"

class Application
{
public:
    int width, height;
    HANDLE hOutput;

    Renderer* renderer;

  Application(const short width, const short height, const short fontW, const short fontH, const float targetFPS);
  ~Application();

    void RefreshFrame();

  virtual void onUpdate(float delta) = 0;
  virtual void onRender() = 0;

  void Run();
  void Stop();

private:
	bool running;
	Timer loopTimer;
	float targetFPS;
    COORD dwBufferSize;
    COORD dwBufferCoord;
    SMALL_RECT rcRegion;
};

