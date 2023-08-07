#pragma once

#include "amuse/gl.h"
#include "amuse/bounds.h"

#ifdef AMUSE_USE_IMGUI

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

#endif

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace wm {
	class Window;
}

namespace debug {

    void Log(const std::string& message);

    void Init(wm::Window* window);

    void DrawLine(const glm::vec3& start, const glm::vec3& end, const glm::vec3& color);

    void DrawCube(const glm::vec3& position, const glm::vec3& size, const glm::vec3& color);

    void DrawBounds(const math::Bounds& bounds, const glm::vec3& color);

    void DrawBounds(const math::Bounds2D& bounds, const glm::vec3& color);

    void Draw(gl::Camera& camera);

    void DrawGui();

    void InitFrame();
    
    void DrawStaticLine(const glm::vec3& start, const glm::vec3& end, const glm::vec3& color);
}