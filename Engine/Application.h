#pragma once
#include <Windows.h>
#include <iostream>
#include <sstream>

#include "Timer.h"

class Application
{
public:
  CHAR_INFO* buffer;
  int width, height;
  HANDLE hOutput;

  CHAR_INFO* GetCharAt(const int& x, const int& y);

  Application(const short width, const short height, const short fontW, const short fontH, const float targetFPS);
  ~Application();

  virtual void onUpdate(float delta) = 0;
  virtual void onRender() = 0;

  void Run();
  void Stop();

private:
	bool running;
	Timer loopTimer;
	float targetFPS;
};

