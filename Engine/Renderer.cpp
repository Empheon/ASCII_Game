#include "Renderer.h"

Renderer::Renderer(const short &width, const short &height)
{
    this->width = width;
    this->height = height;

    buffer = new CHAR_INFO[width * height];

    std::memset(buffer, 0, sizeof(CHAR_INFO) * width * height);
}

Renderer::~Renderer()
{
    delete[] buffer;
}


CHAR_INFO* Renderer::GetCharAt(const int& x, const int& y)
{
    return &buffer[y * this->width + x];
}

void Renderer::DrawRect(const short& x, const short& y, const short& width, const short& height, const char& c, const WORD& attributes) {
    CHAR_INFO* ci;
    for (int i = max(0, x); i < min((short)(x + width), this->width); i++) {
        for (int j = max(0, y); j < min((short)(y + height), this->height); j++) {
            ci = GetCharAt(i, j);
            ci->Char.AsciiChar = c;
            ci->Attributes = attributes;
        }
    }
}
