#include "Texture.h"

Texture::Texture(int width, int height, std::wstring data)
	: width(width), height(height), data(data)
{
}

std::wstring* Texture::GetData()
{
	return &data;
}

int Texture::GetWidth() const
{
	return width;
}

int Texture::GetHeight() const
{
	return height;
}