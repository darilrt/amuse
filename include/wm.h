#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <SDL.h>

namespace wm {
	class Window {
	public:
		Window();
		Window(int width, int height);
		Window(const char* title, int width, int height);

		~Window();

		inline void SwapBuffers() { SDL_GL_SwapWindow(window); }

		inline void SetTitle(const char* title) { SDL_SetWindowTitle(window, title); }

		inline void SetSize(int width, int height) {
			SDL_SetWindowSize(window, width, height); 
			this->width = width;
			this->height = height;
		}

		inline void SetFullscreen(bool fullscreen) { SDL_SetWindowFullscreen(window, fullscreen ? SDL_WINDOW_FULLSCREEN : 0); }

		inline void SetVSync(bool vsync) { SDL_GL_SetSwapInterval(vsync ? 1 : 0); }

		inline void SetCursorVisible(bool visible) { SDL_ShowCursor(visible ? SDL_ENABLE : SDL_DISABLE); }

		inline void SetCursorLocked(bool locked) { SDL_SetRelativeMouseMode(locked ? SDL_TRUE : SDL_FALSE); }

		inline void SetCursor(int x, int y) { SDL_WarpMouseInWindow(window, x, y); }

		inline void SetCursor(glm::ivec2 position) { SDL_WarpMouseInWindow(window, position.x, position.y); }

		inline void SetRelativeCursorMode(bool relative) { SDL_SetRelativeMouseMode(relative ? SDL_TRUE : SDL_FALSE); }

		inline void SetCursorConfine(bool confine) { SDL_SetWindowGrab(window, confine ? SDL_TRUE : SDL_FALSE); }

		inline void GetCursor(int* x, int* y) { SDL_GetMouseState(x, y); }

		inline int GetWidth() { return width; }

		inline int GetHeight() { return height; }

		inline bool IsOpen() { return running; }

		inline void Close() { running = false; }

	private:
		SDL_Window* window;
		SDL_GLContext context;

		int width;
		int height;

		bool running;
	};
}
