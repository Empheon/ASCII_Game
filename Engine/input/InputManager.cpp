#include "InputManager.h"

#include <sstream>

InputManager::InputManager() {
}

InputManager::~InputManager() {
}

bool InputManager::SearchGamepads()
{
    DWORD dwResult;

    int prevGamepadsCount = gamepads.size();
    gamepads.clear();

    for (DWORD i = 0; i < MAX_CONNECTED_GAMEPADS; ++i)
    {
        XINPUT_STATE state;
        ZeroMemory(&state, sizeof(XINPUT_STATE));

        // Simply get the state of the controller from XInput.
        dwResult = XInputGetState(i, &state);

        if (dwResult != ERROR_SUCCESS) {
            continue;
        }

        gamepads.push_back(Gamepad(i, state));        
    }
        
    std::wstringstream ss;
    ss << "Gamepads : " << gamepads.size() << std::endl;
    OutputDebugString(ss.str().c_str());

    return prevGamepadsCount != gamepads.size();
}

Gamepad* InputManager::GetGamepad(int i) {
    if (gamepads.size() <= i) {
        return nullptr;
    }
    return &gamepads[i];
}

void InputManager::Update()
{
    for (Gamepad gp : gamepads) {
        gp.Update();
    }
}

size_t InputManager::GetConnectedGamepadCount() {
    return gamepads.size();
}
