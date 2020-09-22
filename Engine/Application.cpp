#include "Application.h"

Application::Application(const short width, const short height, const short fontW, const short fontH, const float targetFPS)
    : width(width), height(height), targetFPS(targetFPS)
{
    hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);

    dwBufferSize = { width, height };
    dwBufferCoord = { 0, 0 };
    rcRegion = { 0, 0, width - 1, height - 1 };

    SetLastError(NO_ERROR);

    // Set windows style
    LONG_PTR new_style = (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU);
    HWND hwnd_console = GetConsoleWindow();
    LONG_PTR style_ptr = SetWindowLongPtr(hwnd_console, GWL_STYLE, new_style);

    // Set initial size
    SetWindowPos(hwnd_console, HWND_TOP, 0, 0, 1, 1, SWP_FRAMECHANGED | SWP_NOMOVE);

    // Set font
    CONSOLE_FONT_INFOEX font;
    lstrcpyW(font.FaceName, L"Consolas");
    font.dwFontSize.X = fontW;
    font.dwFontSize.Y = fontH;
    font.FontFamily = FF_DONTCARE;
    font.FontWeight = FW_NORMAL;
    font.cbSize = sizeof(font);
    SetCurrentConsoleFontEx(hOutput, true, &font);

    // Set window size
    SetConsoleScreenBufferSize(hOutput, dwBufferSize);
    SetConsoleWindowInfo(hOutput, true, &rcRegion);

    // Get window info for setting the correct size
    CONSOLE_SCREEN_BUFFER_INFO sbInfo;
    GetConsoleScreenBufferInfo(hOutput, &sbInfo);

    // Set window size
    int posx = (GetSystemMetrics(SM_CXSCREEN) - (sbInfo.dwSize.X * fontW)) / 2;
    int posy = (GetSystemMetrics(SM_CYSCREEN) - (sbInfo.dwSize.Y * fontH)) / 2;
    SetWindowPos(hwnd_console, HWND_TOP, posx, posy, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE);


    // Show window 
    ShowWindow(hwnd_console, SW_SHOW);

    this->renderer = new Renderer(width, height);
}

void Application::RefreshFrame() {
    WriteConsoleOutput(hOutput, renderer->buffer, dwBufferSize, dwBufferCoord, &rcRegion);
}

Application::~Application() {
}

void Application::Run()
{
    running = true;
    loopTimer.start();

    double frameMillis = 1.0 / targetFPS;
    double delta = 0.0;
    double lastTime = loopTimer.getElapsedSeconds();

#ifdef _DEBUG
    double lastPrint = 0.0;
    int updates = 0;
    int frames = 0;
#endif

    input.SearchGamepads();

    while (running) {
        double currentTime = loopTimer.getElapsedSeconds();
        delta += currentTime - lastTime;
        lastTime = currentTime;

        UpdateInputs();

        while (delta >= frameMillis) {
            OnUpdate(delta);
#ifdef _DEBUG
            updates++;
#endif
            delta -= frameMillis;
        }

        OnRender();

#ifdef _DEBUG
        frames++;
        if (currentTime - lastPrint > 1.0) {
            std::wstringstream ss;
            ss << "[GameLoop] updates: " << updates << " | frames: " << frames << std::endl;
            OutputDebugString(ss.str().c_str());
            updates = 0;
            frames = 0;
            lastPrint = currentTime;
        }
#endif
    }
}

void Application::Stop() {
    running = false;
}

void Application::UpdateInputs() {
    for (int i = 0; i < input.GetConnectedGamepadCount(); ++i) {
        input.GetGamepad(i)->Update();
    }
}
