#pragma once
#include <algorithm>
#include <Windows.h>

class Renderer
{
public:
    short width;
    short height;
    CHAR_INFO* buffer;

    Renderer(const short& width, const short& height);
    ~Renderer();

    CHAR_INFO* GetCharAt(const int& x, const int& y);

    void DrawRect(const short& x, const short& y, const short& width, const short& height, const char& c, const WORD& attributes);
};

