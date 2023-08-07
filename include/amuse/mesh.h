#pragma once

#include "amuse/gl.h"
#include "amuse/buffer.h"

#include <cstdint>
#include <vector>
#include <glm/glm.hpp>

namespace gl {

    class Mesh {
    public:
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> uvs;
        std::vector<glm::u32vec3> indices;
        
        Mesh();
        Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<glm::vec2> uvs, std::vector<glm::u32vec3> indices);
        ~Mesh() = default;

        inline void Bind() { vao.Bind(); }
        inline void Unbind() { vao.Unbind(); }

        inline void SetVertices(std::vector<glm::vec3> vertices) { this->vertices = vertices;}

        inline void SetNormals(std::vector<glm::vec3> normals) { this->normals = normals; }

        inline void SetUVs(std::vector<glm::vec2> uvs) { this->uvs = uvs; }

        inline void SetIndices(std::vector<glm::u32vec3> indices) { this->indices = indices; }

        inline void DrawTriangles() { vao.DrawTriangles(ibo); }

        void Bake();

    private:
        VertexArray vao;
        VertexBuffer vbo;
        VertexBuffer nbo;
        VertexBuffer tbo;
        IndexBuffer ibo;
    };

}