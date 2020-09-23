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
    int8_t* depthBuffer;

    float shakeForce = 0;

    Renderer(const short& width, const short& height);
    ~Renderer();

    inline CHAR_INFO* GetCharAt(const int x, const int y);
    inline int8_t GetDepthAt(const int x, const int y);

    void Clear(const wchar_t c, const WORD& attributes);
    void ClearDepth();
    void SetDepth(const int x, const int y, int8_t z);
    void DrawChar(const int x, const int y, const wchar_t c, const WORD& attributes, int8_t z = 0);
    void Draw4DLine(const int x1, const int y1, const int x2, const int y2, const WORD& attributes, int8_t z = 0);
    void DrawRect(const int x, const int y, const int width, const int height, const wchar_t c, const WORD& attributes, int8_t z = 0);
    void DrawTexture(const int x, const int y, const Texture& tex, const WORD& attributes, int8_t z = 0);
    void DrawString(const int x, const int y, const std::wstring& text, const WORD& attributes, int8_t z = 0);

    void DoScreenShake(float force);

    void Update();
};

