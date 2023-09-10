#pragma once

#include "amuse/gl.h"
#include "amuse/buffer.h"

#include <cstdint>
#include <vector>
#include <glm/glm.hpp>

namespace gl {

    class Mesh {
        class VertexBufferReference {
        public:
            VertexBufferReference(VertexBuffer* buffer, uint32_t count, gl::Type type) {
                this->buffer = buffer;
                this->count = count;
                this->type = type;
            }

            ~VertexBufferReference() = default;

            inline VertexBuffer* GetBuffer() const { return buffer; }
            inline uint32_t GetCount() const { return count; }
            inline gl::Type GetType() const { return type; }

        private:
            VertexBuffer* buffer;
            uint32_t count;
            gl::Type type;
        };

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

        inline void DrawTriangles() { if (!baked) { return; } vao.DrawTriangles(ibo); }

        inline void AddVertexBuffer(VertexBuffer* buffer, gl::Type type, uint32_t count) { buffers.push_back(VertexBufferReference(buffer, count, type)); }

        void Bake();

    private:
        bool baked = false;
        VertexArray vao;
        VertexBuffer vbo;
        VertexBuffer nbo;
        VertexBuffer tbo;
        IndexBuffer ibo;

        std::vector<VertexBufferReference> buffers;
    };

}