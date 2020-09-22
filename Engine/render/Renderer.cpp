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

void Renderer::DrawChar(const short& x, const short& y, const char& c, const WORD& attributes)
{
}

void Renderer::DrawRect(const short& x, const short& y, const short& width, const short& height, const char& c, const WORD& attributes) {
    CHAR_INFO* ci;
    for (int i = max(0, x); i < min((short)(x + width), this->width); i++) {
        for (int j = max(0, y); j < min((short)(y + height), this->height); j++) {
            ci = GetCharAt(i, j);
            ci->Char.UnicodeChar = c;
            ci->Attributes = attributes;
        }
    }
}

void Renderer::DrawSprite(const short& x, const short& y, Texture& tex, const WORD& attributes)
{
    CHAR_INFO* ci;
    std::wstring* data = tex.GetData();

    for (size_t yy = 0; yy < tex.GetHeight(); ++yy) {
        for (size_t xx = 0; xx < tex.GetWidth(); ++xx) {
            ci = GetCharAt(x + xx, y + yy);
            ci->Char.UnicodeChar = data->at(yy * tex.GetWidth() + xx);
            ci->Attributes = attributes;
        }
    }
}
