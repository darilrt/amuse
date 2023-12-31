#include "amuse/mesh.h"

gl::Mesh::Mesh() { }

gl::Mesh::Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<glm::vec2> uvs, std::vector<glm::u32vec3> indices) {
    this->vertices = vertices;
    this->normals = normals;
    this->uvs = uvs;
    this->indices = indices;

    Bake();
}

void gl::Mesh::Bake() {
    baked = true;

    vao.Bind();

    vbo.SetData(vertices.data(), vertices.size() * sizeof(glm::vec3), gl::VertexBuffer::Static);
    vao.AddBuffer(vbo, gl::Type::Float, 3);

    nbo.SetData(normals.data(), normals.size() * sizeof(glm::vec3), gl::VertexBuffer::Static);
    vao.AddBuffer(nbo, gl::Type::Float, 3);

    tbo.SetData(uvs.data(), uvs.size() * sizeof(glm::vec2), gl::VertexBuffer::Static);
    vao.AddBuffer(tbo, gl::Type::Float, 2);

    ibo.SetData(indices.data(), indices.size() * 3);

    for (auto& bufferReference : buffers) {
        vao.AddBuffer(*bufferReference.GetBuffer(), bufferReference.GetType(), bufferReference.GetCount());
    }

    vao.Unbind();
    ibo.Unbind();

    vertices = std::vector<glm::vec3>();
    normals = std::vector<glm::vec3>();
    uvs = std::vector<glm::vec2>();
    indices = std::vector<glm::u32vec3>();
}
