#pragma once

#include "gl.h"

#include <glm/glm.hpp>
#include <cstdint>
#include <vector>

namespace gl {
    
    class WireBatch {
    public:
        WireBatch();

        void AddLine(const glm::vec3& start, const glm::vec3& end, const glm::vec3& color);
        
        void Draw(gl::Camera& camera);

        void Bake();

        void Clear();

    private:
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> colors;

        gl::VertexArray vao; 
        gl::VertexBuffer vbo;
        gl::VertexBuffer cbo;
    };
         

}
