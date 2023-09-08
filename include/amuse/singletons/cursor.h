#pragma once

#include "amuse/singletons/screen.h"

class Cursor {
public:
	static inline void SetCursorVisible(bool visible) { Screen::Get()->window->SetCursorVisible(visible); }

	static inline void SetCursorLocked(bool locked) { Screen::Get()->window->SetCursorLocked(locked); }

	static inline void SetCursor(int x, int y) { Screen::Get()->window->SetCursor(x, y); }

	static inline void SetCursor(glm::ivec2 position) { Screen::Get()->window->SetCursor(position.x, position.y); }

	static inline void SetRelativeCursorMode(bool relative) { Screen::Get()->window->SetRelativeCursorMode(relative); }

	static inline void SetCursorConfine(bool confine) { Screen::Get()->window->SetCursorConfine(confine); }
};

