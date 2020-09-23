#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <locale>

class Texture
{
public:
	Texture(int width, int height, std::wstring data, bool alpha = false);
	Texture();

	const std::wstring* GetData() const;
	int GetWidth() const;
	int GetHeight() const;
	bool IsAlpha() const;

	
private:
	int width, height;
	bool alpha;
	std::wstring data;
};

