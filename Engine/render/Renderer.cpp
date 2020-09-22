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
    CHAR_INFO* ci = GetCharAt(x, y);
    ci->Char.UnicodeChar = c;
    ci->Attributes = attributes;
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

    if (x < -tex.GetWidth() || x >= width || y < -tex.GetHeight() || y >= height)
        return;

    int leftCut = abs(min(x, 0));
    int topCut = abs(min(y, 0));
 
    for (size_t yy = max(0, y), ys = topCut; ys < tex.GetHeight() && yy < height; ++yy, ++ys) {
        for (size_t xx = max(0, x), xs = leftCut; xs < tex.GetWidth() && xx < width; ++xx, ++xs) {
            ci = GetCharAt(xx, yy);
            ci->Char.UnicodeChar = data->at(ys * tex.GetWidth() + xs);
            ci->Attributes = attributes;
        }
    }
}
