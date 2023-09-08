#include "amuse/wm.h"
#include "amuse/gl.h"

wm::Window::Window() {
	window = SDL_CreateWindow("Title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL);
	context = SDL_GL_CreateContext(window);

	gl::Init();

	running = true;

	this->width = 640;
	this->height = 480;
}

wm::Window::Window(int width, int height) {
	window = SDL_CreateWindow("Title", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
	context = SDL_GL_CreateContext(window);

	gl::Init();

	running = true;

	this->width = width;
	this->height = height;
}

wm::Window::Window(const char* title, int width, int height) {
	window = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		width, height,
		SDL_WINDOW_OPENGL
	);
	context = SDL_GL_CreateContext(window);

	gl::Init();

	running = true;

	this->width = width;
	this->height = height;
}

wm::Window::~Window() {
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}