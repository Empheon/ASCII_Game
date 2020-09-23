#include "Texture.h"

Texture::Texture(int width, int height, std::wstring data, bool alpha)
	: width(width), height(height), data(data), alpha(alpha) {
}

Texture::Texture()
{
}

std::wstring* Texture::GetData() {
	return &data;
}

int Texture::GetWidth() const {
	return width;
}

int Texture::GetHeight() const {
	return height;
}

bool Texture::IsAlpha() const {
	return alpha;
}