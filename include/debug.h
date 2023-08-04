#pragma once

#include "gl.h"
#include "bounds.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace debug {

    void DrawLine(const glm::vec3& start, const glm::vec3& end, const glm::vec3& color);

    void DrawCube(const glm::vec3& position, const glm::vec3& size, const glm::vec3& color);

    void DrawBounds(const math::Bounds& bounds, const glm::vec3& color);

    void Draw(gl::Camera& camera);
    
}