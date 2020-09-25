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
    if (x < 0 || y < 0 || x >= width || y >= height)
        return;
    if (z < GetDepthAt(x, y))
        return;
    CHAR_INFO* ci = GetCharAt(x, y);
    ci->Char.UnicodeChar = c;
    ci->Attributes = attributes;
    SetDepth(x, y, z);
}

void Renderer::Draw4DLine(const int x1, const int y1, const int x2, const int y2, const WORD& attributes, int8_t z, const wchar_t c) {
    wchar_t cUsed = c;
    if (y1 == y2 && y1 >= 0) { // Draw an horizontal line
        if (c == 0) cUsed = L'\u2500';
        for (int x = max(0, min(x1, x2)); x < max(x1, x2) && x < width; x++) {
            DrawChar(x, y1, c, attributes, z);
        }
    } else if (x1 == x2 && x1 >= 0) { // Draw a vertical line
        if (c == 0) cUsed = L'\u2502';
        for (int y = max(0, min(y1, y2)); y < max(y1, y2) && y < height; y++) {
            DrawChar(x1, y, c, attributes, z);
        }
    }
}

void Renderer::DrawRect(const int x, const int y, const int width, const int height, const wchar_t c, const WORD& attributes, int8_t z) {
    for (int i = max(0, x); i < min((short)(x + width), this->width); i++) {
        for (int j = max(0, y); j < min((short)(y + height), this->height); j++) {
            DrawChar(i, j, c, attributes, z);
        }
    }
}

void Renderer::DrawCircle(const int cx, const int cy, const int radius, const wchar_t c, const WORD& attributes, int8_t z) {
    int maxX = radius;
    for (int y = 0; y <= radius; ++y) {
        for (int x = maxX; x >= 0; --x) {
            if ((x * x) + (y * y) < (radius * radius)) {
                Draw4DLine(cx - x, cy + y, cx + x, cy + y, attributes, z, c);
                Draw4DLine(cx - x, cy - y, cx + x, cy - y, attributes, z, c);
                maxX = x;
                break;
            }
        }
    }
}

void Renderer::DrawTexture(const int x, const int y, const Texture& tex, const WORD& attributes, int8_t z)
{
    const std::wstring* data = tex.GetData();

    if (x < -tex.GetWidth() || x >= width || y < -tex.GetHeight() || y >= height)
        return;

    int leftCut = abs(min(x, 0));
    int topCut = abs(min(y, 0));
 
    for (size_t yy = max(0, y), ys = topCut; ys < tex.GetHeight() && yy < height; ++yy, ++ys) {
        for (size_t xx = max(0, x), xs = leftCut; xs < tex.GetWidth() && xx < width; ++xx, ++xs) {
            wchar_t c = data->at(ys * tex.GetWidth() + xs);
            if (tex.IsAlpha() && c == ' ') continue;
            DrawChar(xx, yy, c, attributes, z);
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

void Renderer::DoScreenShake(float force) {
    if (force <= shakeForce)
        return;
    shakeForce = force;
}

void Renderer::Update() {
    if (shakeForce < 0.1f) {
        shakeForce = 0;
    }
    shakeForce *= 0.92f;
}
