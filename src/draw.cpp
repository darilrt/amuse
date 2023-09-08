#include "amuse/draw.h"

#include "amuse/gl.h"

#include <glm/glm.hpp>
#include <cstdint>

gl::WireBatch::WireBatch() {
    vao.Bind();
    vbo.Bind();
    vao.AddBuffer<float>(vbo, 3);
    cbo.Bind();
    vao.AddBuffer<float>(cbo, 3);
    vao.Unbind();
}

void gl::WireBatch::AddLine(const glm::vec3 &start, const glm::vec3 &end, const glm::vec3 &color) {
    vertices.push_back(start);
    vertices.push_back(end);
    colors.push_back(color);
    colors.push_back(color);
}

void gl::WireBatch::Draw(gl::Camera& camera) {
    static gl::Shader shader("assets/shaders/wire.vert", "assets/shaders/wire.frag");

    shader.Bind();
    shader.SetCameraUniforms(camera);
    vao.DrawLines(vertices.size());
    shader.Unbind();
}

void gl::WireBatch::Bake() {
    vbo.SetData(vertices.data(), vertices.size() * sizeof(glm::vec3));
    cbo.SetData(colors.data(), colors.size() * sizeof(glm::vec3));
}

void gl::WireBatch::Clear() {
    vertices.clear();
    colors.clear();
}
