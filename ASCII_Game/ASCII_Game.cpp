#include <iostream>
#include <Application.h>

int main()
{
    Application* app = new Application(48, 48, 12, 12);

    app->renderer->DrawRect(2, 2, 5, 5, 'o', 0x0e);
    app->RefreshFrame();

    std::cin.get();

    delete app;

    return 0;
}
