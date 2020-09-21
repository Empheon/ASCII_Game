#include <iostream>
#include <Application.h>

int main()
{
    Application* app = new Application(48, 48, 12, 12);

    std::cin.get();

    delete app;

    return 0;
}
