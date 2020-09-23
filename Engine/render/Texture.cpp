#include "Texture.h"

Texture::Texture(int width, int height, std::wstring data, bool alpha)
	: width(width), height(height), data(data), alpha(alpha) {
}

Texture::Texture()
{
}

const std::wstring* Texture::GetData() const {
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