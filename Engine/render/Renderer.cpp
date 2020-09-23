#include "Renderer.h"

Renderer::Renderer(const short &width, const short &height)
{
    this->width = width;
    this->height = height;

    buffer = new CHAR_INFO[(int) width * height];
    depthBuffer = new int8_t[(int) width * height];

    std::memset(buffer, 0, sizeof(CHAR_INFO) * width * height);
}

Renderer::~Renderer()
{
    delete[] buffer;
    delete[] depthBuffer;
}


CHAR_INFO* Renderer::GetCharAt(const int x, const int y)
{
    return &buffer[y * this->width + x];
}

int8_t Renderer::GetDepthAt(const int x, const int y)
{
    return depthBuffer[y * this->width + x];
}

void Renderer::Clear(const wchar_t c, const WORD& attributes)
{
    for (int i = 0; i < width * height; ++i) {
        buffer[i].Char.UnicodeChar = c;
        buffer[i].Attributes = attributes;
    }
    ClearDepth();
}

void Renderer::ClearDepth() {
    std::memset(depthBuffer, -128, sizeof(int8_t) * width * height);
}

void Renderer::SetDepth(const int x, const int y, int8_t z) {
    depthBuffer[y * width + x] = z;
}

void Renderer::DrawChar(const int x, const int y, const wchar_t c, const WORD& attributes, int8_t z) {
    if (z < GetDepthAt(x, y))
        return;
    CHAR_INFO* ci = GetCharAt(x, y);
    ci->Char.UnicodeChar = c;
    ci->Attributes = attributes;
    SetDepth(x, y, z);
}

void Renderer::DrawRect(const int x, const int y, const int width, const int height, const wchar_t c, const WORD& attributes, int8_t z) {
    for (int i = max(0, x); i < min((short)(x + width), this->width); i++) {
        for (int j = max(0, y); j < min((short)(y + height), this->height); j++) {
            DrawChar(i, j, c, attributes, z);
        }
    }
}

void Renderer::DrawSprite(const int x, const int y, Texture& tex, const WORD& attributes, int8_t z)
{
    std::wstring* data = tex.GetData();

    if (x < -tex.GetWidth() || x >= width || y < -tex.GetHeight() || y >= height)
        return;

    int leftCut = abs(min(x, 0));
    int topCut = abs(min(y, 0));
 
    for (size_t yy = max(0, y), ys = topCut; ys < tex.GetHeight() && yy < height; ++yy, ++ys) {
        for (size_t xx = max(0, x), xs = leftCut; xs < tex.GetWidth() && xx < width; ++xx, ++xs) {
            DrawChar(xx, yy, data->at(ys * tex.GetWidth() + xs), attributes, z);
        }
    }
}

void Renderer::DrawString(const int x, const int y, const std::wstring& text, const WORD& attributes, int8_t z) {
    int minX = -(int)text.size();
    if (x < minX || x >= width || y < 0 || y >= height)
        return;

    int leftCut = abs(min(x, 0));
    for (size_t xx = max(0, x), xs = leftCut; xs < text.size() && xx < width; ++xx, ++xs) {
        DrawChar(xx, y, text.at(xs), attributes, z);
    }
}
