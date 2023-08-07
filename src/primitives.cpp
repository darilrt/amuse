#include "amuse/primitives.h"

gl::Mesh* primitive::CreateQuad() {
    const std::vector<glm::vec3> vertices = {
        { -0.5f, -0.5f, 0.0f },
        { 0.5f, -0.5f, 0.0f },
        { 0.5f, 0.5f, 0.0f },
        { -0.5f, 0.5f, 0.0f },
    };

    const std::vector<glm::vec3> normals = {
        { 0.0f, 0.0f, 1.0f },
        { 0.0f, 0.0f, 1.0f },
        { 0.0f, 0.0f, 1.0f },
        { 0.0f, 0.0f, 1.0f },
    };

    const std::vector<glm::vec2> uvs = {
        { 0.0f, 1.0f },
        { 1.0f, 1.0f },
        { 1.0f, 0.0f },
        { 0.0f, 0.0f },
    };

    const std::vector<glm::u32vec3> indices = {
        { 0, 1, 2 },
        { 2, 3, 0 },
    };

    return new gl::Mesh(vertices, normals, uvs, indices);
}
