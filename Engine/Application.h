#pragma once
#include <Windows.h>
#include <iostream>
#include "Renderer.h"

class Application
{
public:
    int width, height;
    HANDLE hOutput;

    Renderer* renderer;

    Application(const short width, const short height, const short fontW, const short fontH);
    void RefreshFrame();
    ~Application();

private:
    COORD dwBufferSize;
    COORD dwBufferCoord;
    SMALL_RECT rcRegion;
};

