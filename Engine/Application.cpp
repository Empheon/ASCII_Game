#include "Application.h"
#include "scene/Scene.h"

Application::Application(const short width, const short height, const short fontW, const short fontH, const float targetFPS)
    : targetFPS(targetFPS), appTicks(0)
{
    Application::width = width;
    Application::height = height;

    hOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);

    dwBufferSize = { width, height };
    dwBufferCoord = { 0, 0 };
    rcRegion = { 0, 0, width - 1, height - 1 };

    SetLastError(NO_ERROR);

    // Set windows style
    LONG_PTR new_style = (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU);
    hwnd_console = GetConsoleWindow();
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
    posx = (GetSystemMetrics(SM_CXSCREEN) - (sbInfo.dwSize.X * fontW)) / 2;
    posy = (GetSystemMetrics(SM_CYSCREEN) - (sbInfo.dwSize.Y * fontH)) / 2;
    SetWindowPos(hwnd_console, HWND_TOP, posx, posy, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE);

    // Hide cursor 
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOutput, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hOutput, &cursorInfo);

    // Show window 
    ShowWindow(hwnd_console, SW_SHOW);

    renderer = new Renderer(width, height);
}

void Application::RefreshFrame() {
    if (renderer->freezeFrameCount > 0) return;

    int rxSign = ((double)rand() / RAND_MAX) > 0.5f ? 1 : -1;
    int rySign = ((double)rand() / RAND_MAX) > 0.5f ? 1 : -1;

    double rx = rxSign * (((double)rand() / (RAND_MAX)) + 1) * renderer->shakeForce;
    double ry = rySign * (((double)rand() / (RAND_MAX)) + 1) * renderer->shakeForce;

    WriteConsoleOutputW(hOutput, renderer->buffer, dwBufferSize, dwBufferCoord, &rcRegion);

    SetWindowPos(hwnd_console, HWND_TOP, posx + rx * 5, posy + ry * 5, 0, 0, SWP_FRAMECHANGED | SWP_NOSIZE);
}

Application::~Application() {
    delete renderer;
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

    OnInit();

    while (running) {
        double currentTime = loopTimer.getElapsedSeconds();
        delta += currentTime - lastTime;
        lastTime = currentTime;

        while (delta >= frameMillis) {
            UpdateInputs();
            Update();
#ifdef _DEBUG
            updates++;
#endif
            appTicks++;
            delta -= frameMillis;
        }

        Draw();

        RefreshFrame();

#ifdef _DEBUG
        frames++;
        if (currentTime - lastPrint > 1.0) {
            std::wstringstream ss;
            ss << "[GameLoop] updates per sec: " << updates << " | fps: " << frames << std::endl;
            OutputDebugString(ss.str().c_str());
            updates = 0;
            frames = 0;
            lastPrint = currentTime;
        }
#endif
        if (sceneToDelete != nullptr) {
            delete sceneToDelete;
            sceneToDelete = nullptr;
        }
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

void Application::Update() {
    
    renderer->Update();

    if (renderer->freezeFrameCount > 0)
        return;

    if (currentScene != nullptr) {
        currentScene->Update();
    }
    OnUpdate();
    particles.Update();
}

void Application::Draw() {
    OnPreDraw();
    if (currentScene != nullptr) {
        currentScene->Draw(renderer);
    }
    particles.Draw(renderer);
    OnPostDraw();
}

size_t Application::GetAppTicks() const
{
    return appTicks;
}

void Application::LoadScene(Scene* scene) {
    if (currentScene != nullptr) {
        sceneToDelete = currentScene;
    }
    currentScene = scene;
    currentScene->parent = this;
    currentScene->OnLoad();
}