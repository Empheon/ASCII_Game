#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <locale>

class Texture
{
public:
	Texture(int width, int height, std::wstring data);

	std::wstring* GetData();
	int GetWidth() const ;
	int GetHeight() const ;

	static Texture LoadFromFile(std::string filename);

private:
	int width, height;
	std::wstring data;
};
