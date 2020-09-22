#pragma once
#include <algorithm>
#include <Windows.h>

#include "Texture.h"

class Renderer
{
public:
    short width;
    short height;
    CHAR_INFO* buffer;

    Renderer(const short& width, const short& height);
    ~Renderer();

    CHAR_INFO* GetCharAt(const int& x, const int& y);

    void Clear(const char& c, const WORD& attributes);
    void DrawChar(const short& x, const short& y, const char& c, const WORD& attributes);
    void DrawRect(const short& x, const short& y, const short& width, const short& height, const char& c, const WORD& attributes);
    void DrawSprite(const short& x, const short& y, Texture& tex, const WORD& attributes);
};

