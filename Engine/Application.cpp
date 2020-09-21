#include "Application.h"

Application::Application(const short width, const short height, const short fontW, const short fontH)
{
  this->width = width;
  this->height = height;

  hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);

  dwBufferSize = { width, height };
  dwBufferCoord = { 0, 0 };
  rcRegion = { 0, 0, width - 1, height - 1 };

  SetLastError(NO_ERROR);

  LONG_PTR new_style = WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL;
  HWND hwnd_console = GetConsoleWindow();
  LONG_PTR style_ptr = SetWindowLongPtr(hwnd_console, GWL_STYLE, new_style);
  SetWindowPos(hwnd_console, 0, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_DRAWFRAME);

  HANDLE outputHandle = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);

  SMALL_RECT tmpRect = { 0, 0, 1, 1 };

  // Set window size
  SetConsoleWindowInfo(hOutput, true, &tmpRect);
  SetConsoleScreenBufferSize(hOutput, dwBufferSize);
  SetConsoleWindowInfo(hOutput, true, &rcRegion);

  // Set font
  CONSOLE_FONT_INFOEX font;
  lstrcpyW(font.FaceName, L"Consolas");
  font.dwFontSize.X = fontW;
  font.dwFontSize.Y = fontH;
  font.FontFamily = FF_DONTCARE;
  font.FontWeight = FW_NORMAL;
  font.cbSize = sizeof(font);
  SetCurrentConsoleFontEx(hOutput, true, &font);

  //show window after updating
  ShowWindow(hwnd_console, SW_SHOW);

  this->renderer = new Renderer(width, height);
}

void Application::RefreshFrame() {
    WriteConsoleOutput(hOutput, renderer->buffer, dwBufferSize, dwBufferCoord, &rcRegion);
}

Application::~Application()
{
}
