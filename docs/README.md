# Amuse Engine Documentation

## Index

- [FAQ](#faq)
- [Features](#features)
- [Class Reference](#class-reference)

## FAQ

### What is Amuse?

Amuse is a game engine written in C++ and uses SDL2 and OpenGL. It's currently in development.

### How do I build Amuse?

Amuse its commonly build inside a project that uses it.

### Which dependencies does Amuse have?

- SDL2
- OpenGL
- GLEW
- GLM

### Which platforms does Amuse support?

Amuse is currently being developed on Windows, but it should work on Linux and Mac OS X (not tested yet).

## Features

### Platform

- [x] Windows

### Graphics

The graphics module is based on OpenGL 3.3.

- [x] OpenGL 3.3
- [x] Shaders
- [x] Textures

### Input

- [x] Input system based on events (SDL2)
- [x] Keyboard
- [x] Mouse

## Class Reference

- [ecs](#ecs)
    - [Component](#component)
    - [Entity](#entity)
    - [System](#system)
- [gl](#gl)
    - [Shader](#shader)
    - [Texture](#texture)
- [wm](#wm)
    - [Window](#wmwindow)



### wm::Window

Window class for creating and managing a window.

#### Methods

- [Window()](#window)
- [Window(int width, int height)](#windowint-width-int-height)
- [Window(const char* title, int width, int height)](#windowconst-char-title-int-width-int-height)
- [~Window()](#window)
- [Window::SwapBuffers()](#windowswapbuffers) 
- [Window::SetTitle(const char* title)](#windowsettitleconst-char-title)
- [Window::SetSize(int width, int height)](#windowsetsizeint-width-int-height)
- [Window::SetFullscreen(bool fullscreen)](#windowsetfullscreenbool-fullscreen)
- [Window::SetVSync(bool vsync)](#windowsetvsyncbool-vsync)
- [Window::SetCursorVisible(bool visible)](#windowsetcursorvisiblebool-visible)
- [Window::SetCursorLocked(bool locked)](#windowsetcursorlockedbool-locked)
- [Window::SetCursor(int x, int y)](#windowsetcursorint-x-int-y)
- [Window::SetCursor(glm::ivec2 position)](#windowsetcursorglmivec2-position)
- [Window::SetRelativeCursorMode(bool relative)](#windowsetrelativecursormodebool-relative)
- [Window::SetCursorConfine(bool confine)](#windowsetcursorconfinebool-confine)
- [Window::GetCursor(int* x, int* y)](#windowgetcursorint-x-int-y)
- [Window::GetWidth()](#windowgetwidth)
- [Window::GetHeight()](#windowgetheight)
- [Window::IsOpen()](#windowisopen)
- [Window::Close()](#windowclose)
    

#### Constructors

```c++
Window()
```
Constructs a window with the default title, width, and height.

```c++
Window(int width, int height)
```

Constructs a window with the default title and the specified width and height.

```c++
Window(const char* title, int width, int height)
```

Constructs a window with the specified title, width, and height.

#### Destructor

```c++
~Window()
```	

Destructs the window.

#### Window::SwapBuffers()

Swaps the front and back buffers.

#### Window::SetTitle(const char* title)

Sets the window title.

#### Window::SetSize(int width, int height)

Sets the window size.

#### Window::SetFullscreen(bool fullscreen)

Sets the window fullscreen mode.

#### Window::SetVSync(bool vsync)

Sets the window vertical sync.

#### Window::SetCursorVisible(bool visible)

Sets the window cursor visibility.

#### Window::SetCursorLocked(bool locked)

Sets the window cursor locked.

#### Window::SetCursor(int x, int y)

Sets the window cursor position.

#### Window::SetCursor(glm::ivec2 position)

Sets the window cursor position.

#### Window::SetRelativeCursorMode(bool relative)

Sets the window relative cursor mode.

#### Window::SetCursorConfine(bool confine)

Sets the window cursor confine.

#### Window::GetCursor(int* x, int* y)

Gets the window cursor position.

#### Window::GetWidth()

Gets the window width.

#### Window::GetHeight()

Gets the window height.

#### Window::IsOpen()

Returns true if the window is open.

#### Window::Close()

Closes the window.
