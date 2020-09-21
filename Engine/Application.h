#pragma once
#include <Windows.h>
#include <iostream>

class Application
{
public:
  CHAR_INFO* buffer;
  int width, height;
  HANDLE hOutput;

  CHAR_INFO* GetCharAt(const int& x, const int& y);

  Application(const short width, const short height, const short fontW, const short fontH);
  ~Application();
};

