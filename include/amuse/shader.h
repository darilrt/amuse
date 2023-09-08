#pragma once

#include "amuse/camera.h"
#include "amuse/transform.h"
#include "amuse/texture.h"

#include <cstdint>
#include <string>

#define SHADER_UNIFORM_MODEL "model"
#define SHADER_UNIFORM_VIEW "view"
#define SHADER_UNIFORM_PROJECTION "projection"

namespace gl {
    
    class Shader {
    public:
        Shader(const char* vertexPath, const char* fragmentPath);
        ~Shader();
        
        void Bind();

        void Unbind();

        void Reload();

        static Shader& LoadAsset(const std::string& assetPath);

        // Camera Uniforms (View and Projection)
        void SetCameraUniforms(const Camera& camera);

        // Model Transform Uniform
        void SetModelTransform(const Transform& transform);

        // Set Sampler2D Uniform
        void SetSampler2D(const char* name, Texture* texture);

        // Set int Uniform
        void SetUniform1i(const char* name, int value);
        
        // Set IntVector2 Uniform
        void SetUniform2i(const char* name, int v0, int v1);

        // Set IntVector3 Uniform
        void SetUniform3i(const char* name, int v0, int v1, int v2);

        // Set IntVector4 Uniform
        void SetUniform4i(const char* name, int v0, int v1, int v2, int v3);

        // Set Int Uniform Array
        void SetUniform1iv(const char* name, int* value, int count);

        // Set float Uniform
        void SetUniform1f(const char* name, float value);
        
        // Set Vector2 Uniform
        void SetUniform2f(const char* name, float v0, float v1);

        // Set Vector3 Uniform
        void SetUniform3f(const char* name, float v0, float v1, float v2);

        // Set Vector4 Uniform
        void SetUniform4f(const char* name, float v0, float v1, float v2, float v3);

        // Set Float Uniform Array
        void SetUniform1fv(const char* name, float* value, int count);

        // Set Matrix4 Uniform
        void SetUniformMatrix4fv(const char* name, float* value);

        // Check if the shader is valid
        bool IsValid() { return valid; }

    private:
        uint32_t textureCount;
        uint32_t program;
        bool valid;

        time_t vertexLastModified;
        time_t fragmentLastModified;
        std::string vertexPath;
        std::string fragmentPath;
    };

}