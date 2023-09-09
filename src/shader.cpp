#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/glew.h>
#include <GL/gl.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "amuse/gl.h"
#include "amuse/gldefs.h"
#include "amuse/shader.h"
#include "amuse/shader.h"

void PrintShaderLog_impl(int32_t shader);
bool CreateShader_impl(const char* vertexPath, const char* fragmentPath, uint32_t* program);
time_t GetLastModifiedTime(const char* path);

gl::Shader::Shader(const char *vertexPath, const char *fragmentPath) {
    valid = CreateShader_impl(vertexPath, fragmentPath, &program);

    this->vertexPath = vertexPath;
    this->fragmentPath = fragmentPath;
    vertexLastModified = GetLastModifiedTime(vertexPath);
    fragmentLastModified = GetLastModifiedTime(fragmentPath);
}

gl::Shader::~Shader() {
    GL_CALL(glDeleteProgram(program));
}

void gl::Shader::Bind() {
    textureCount = 0;

    GL_CALL(glUseProgram(program));
}

void gl::Shader::Unbind() {
    GL_CALL(glUseProgram(0));
}

void gl::Shader::Reload() {
    time_t vertexLastModified = GetLastModifiedTime(vertexPath.c_str());
    time_t fragmentLastModified = GetLastModifiedTime(fragmentPath.c_str());

    if (vertexLastModified > this->vertexLastModified || fragmentLastModified > this->fragmentLastModified) {
        GL_CALL(glDeleteProgram(program));
        valid = CreateShader_impl(vertexPath.c_str(), fragmentPath.c_str(), &program);
    }

    this->vertexLastModified = vertexLastModified;
    this->fragmentLastModified = fragmentLastModified;
}

gl::Shader &gl::Shader::LoadAsset(const std::string &assetPath) {
    std::string vertexPath = assetPath + ".vert";
    std::string fragmentPath = assetPath + ".frag";
    
    return *new gl::Shader(vertexPath.c_str(), fragmentPath.c_str());
}

void gl::Shader::SetCameraUniforms(const Camera &camera) {
    glm::mat4 view = camera.GetView();
    glm::mat4 projection = camera.GetProjection();
    
    SetUniformMatrix4fv(SHADER_UNIFORM_VIEW, glm::value_ptr(view));
    SetUniformMatrix4fv(SHADER_UNIFORM_PROJECTION, glm::value_ptr(projection));
}

void gl::Shader::SetModelTransform(const Transform &transform) {
    glm::mat4 model = transform.GetModel();
    SetUniformMatrix4fv(SHADER_UNIFORM_MODEL, glm::value_ptr(model));
}

void gl::Shader::SetSampler2D(const char *name, Texture *texture) {
    GL_CALL(glActiveTexture(GL_TEXTURE0 + textureCount));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, texture->GetID()));
    GL_CALL(glUniform1i(glGetUniformLocation(program, name), textureCount));

    textureCount++;
}
void gl::Shader::SetUniform1i(const char *name, int value) {
    GL_CALL(glUniform1i(glGetUniformLocation(program, name), value));
}

void gl::Shader::SetUniform2i(const char *name, int v0, int v1) {
    GL_CALL(glUniform2i(glGetUniformLocation(program, name), v0, v1));
}

void gl::Shader::SetUniform3i(const char *name, int v0, int v1, int v2) {
    GL_CALL(glUniform3i(glGetUniformLocation(program, name), v0, v1, v2));
}

void gl::Shader::SetUniform4i(const char *name, int v0, int v1, int v2, int v3) {
    GL_CALL(glUniform4i(glGetUniformLocation(program, name), v0, v1, v2, v3));
}

void gl::Shader::SetUniform1iv(const char *name, int *value, int count) {
    GL_CALL(glUniform1iv(glGetUniformLocation(program, name), count, value));
}

void gl::Shader::SetUniform1f(const char *name, float value) {
    GL_CALL(glUniform1f(glGetUniformLocation(program, name), value));
}

void gl::Shader::SetUniform2f(const char *name, float v0, float v1) {
    GL_CALL(glUniform2f(glGetUniformLocation(program, name), v0, v1));
}

void gl::Shader::SetUniform3f(const char *name, float v0, float v1, float v2) {
    GL_CALL(glUniform3f(glGetUniformLocation(program, name), v0, v1, v2));
}

void gl::Shader::SetUniform4f(const char *name, float v0, float v1, float v2, float v3) {
    GL_CALL(glUniform4f(glGetUniformLocation(program, name), v0, v1, v2, v3));
}

void gl::Shader::SetUniform1fv(const char *name, float *value, int count) {
    GL_CALL(glUniform1fv(glGetUniformLocation(program, name), count, value));
}

void gl::Shader::SetUniformMatrix4fv(const char *name, float *value) {
    GL_CALL(glUniformMatrix4fv(glGetUniformLocation(program, name), 1, GL_FALSE, value));
}

time_t GetLastModifiedTime(const char* path) {
    struct stat result;
    if (stat(path, &result) == 0) {
        return result.st_mtime;
    }
    else {
        return 0;
    }
}

void PrintShaderLog_impl(int32_t shader) {
	if (glIsShader(shader)) {
		int32_t infoLogLength = 0;
		int32_t maxLength = infoLogLength;

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
		char* infoLog = new char[maxLength];

		glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);

		if (infoLogLength > 0) {
            std::cout << infoLog << std::endl;
		}

		delete[] infoLog;
	}
	else {
		std::string _log = "Name ";
		_log += std::to_string(shader);
		_log += " is not a shader";
		std::cout << _log << std::endl;
	}
}

bool CreateShader_impl(const char* vertexPath, const char* fragmentPath, uint32_t* program) {
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vertexFile;
    std::ifstream fragmentFile;

    vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        vertexFile.open(vertexPath);
        fragmentFile.open(fragmentPath);

        std::stringstream vertexStream, fragmentStream;

        vertexStream << vertexFile.rdbuf();
        fragmentStream << fragmentFile.rdbuf();

        vertexFile.close();
        fragmentFile.close();

        vertexCode = vertexStream.str();
        fragmentCode = fragmentStream.str();
    }
    catch (std::ifstream::failure e) {
        std::cout << "Failed to read shader file" << std::endl;
        return false;
    }

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    uint32_t vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    GL_CALL(glShaderSource(vertex, 1, &vertexSource, nullptr));
    GL_CALL(glCompileShader(vertex));
    PrintShaderLog_impl(vertex);

    if (vertex == 0) {
		std::cout << "Failed to compile vertex shader" << std::endl;
        return false;
	}

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    GL_CALL(glShaderSource(fragment, 1, &fragmentSource, nullptr));
    GL_CALL(glCompileShader(fragment));
    PrintShaderLog_impl(fragment);

    if (fragment == 0) {
        std::cout << "Failed to compile fragment shader" << std::endl;
        return false;
    }

    *program = glCreateProgram();
    GL_CALL(glAttachShader(*program, vertex));
    GL_CALL(glAttachShader(*program, fragment));
    GL_CALL(glLinkProgram(*program));

    int32_t success;
    GL_CALL(glGetProgramiv(*program, GL_LINK_STATUS, &success));

    if (!success) {
		char infoLog[512];
		GL_CALL(glGetProgramInfoLog(*program, 512, nullptr, infoLog));
		std::cout << "Failed to link shader program" << std::endl;
		std::cout << infoLog << std::endl;
        return false;
	}

    GL_CALL(glDeleteShader(vertex));
    GL_CALL(glDeleteShader(fragment));

    return true;
}