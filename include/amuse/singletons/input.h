#pragma once

#include "amuse/enums.h"
#include "amuse/timer.h"

#include <cstdint>
#include <array>

#include <glm/glm.hpp>

class Input {
public:
    inline static bool GetKey(KeyCode key) { return GetInstance().keys[(uint16_t)key]; }

    inline static bool GetKeyDown(KeyCode key) { return GetInstance().keysDown[(uint16_t)key]; }

    inline static bool GetKeyUp(KeyCode key) { return GetInstance().keysUp[(uint16_t)key]; }

    inline static bool GetMouseButton(MouseButton button) { return GetInstance().mouseButtons[(uint8_t)button]; }

    inline static bool GetMouseButtonDown(MouseButton button) { return GetInstance().mouseButtonsDown[(uint8_t)button]; }

    inline static bool GetMouseButtonUp(MouseButton button) { return GetInstance().mouseButtonsUp[(uint8_t)button]; }

    inline static glm::vec2 GetMousePosition() { return GetInstance().mousePosition; }

    inline static glm::vec2 GetMouseDelta() { return GetInstance().mouseDelta; }
    
    inline static float DeltaTime() { return GetInstance().deltaTime; }

    inline static float Time() { return GetInstance().timer.Elapsed(); }

private:
    static Input* instance;
    
    glm::vec2 mousePosition;
    glm::vec2 mouseDelta;
    float deltaTime;
    ut::Timer timer;
    ut::Timer deltaTimer;

	std::array<bool, (uint16_t)KeyCode::NumScancode> keys;
	std::array<bool, (uint16_t)KeyCode::NumScancode> keysDown;
	std::array<bool, (uint16_t)KeyCode::NumScancode> keysUp;
	std::array<bool, 3> mouseButtons;
	std::array<bool, 3> mouseButtonsDown;
	std::array<bool, 3> mouseButtonsUp;

	Input();

    static Input& GetInstance();
};
