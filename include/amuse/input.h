#pragma once

#include "amuse/enums.h"
#include "amuse/timer.h"

#include <cstdint>
#include <array>

#include <glm/glm.hpp>

class Input {
public:
    inline static bool GetKey(KeyCode key) { return instance.keys[(uint16_t)key]; }

    inline static bool GetKeyDown(KeyCode key) { return instance.keysDown[(uint16_t)key]; }

    inline static bool GetKeyUp(KeyCode key) { return instance.keysUp[(uint16_t)key]; }

    inline static bool GetMouseButton(MouseButton button) { return instance.mouseButtons[(uint8_t)button]; }

    inline static bool GetMouseButtonDown(MouseButton button) { return instance.mouseButtonsDown[(uint8_t)button]; }

    inline static bool GetMouseButtonUp(MouseButton button) { return instance.mouseButtonsUp[(uint8_t)button]; }

    inline static glm::vec2 GetMousePosition() { return instance.mousePosition; }
    
    inline static float DeltaTime() { return instance.deltaTime; }

    inline static float Time() { return instance.timer.Elapsed(); }

private:
    static Input instance;
    
    glm::vec2 mousePosition;
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
};
