#include "texture.h"
#include "gldefs.h"

#include <windows.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <cstdint>

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

gl::Texture::Texture() {
    GL_CALL(glGenTextures(1, &id));
}

gl::Texture::~Texture() {
    GL_CALL(glDeleteTextures(1, &id));
}

void gl::Texture::Bind() {
    GL_CALL(glBindTexture(GL_TEXTURE_2D, id));
}

void gl::Texture::Unbind() {
    GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
}

void gl::Texture::SetSize(uint32_t width, uint32_t height) {
    Bind();
    GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, (GLenum)format, width, height, 0, (GLenum)format, GL_UNSIGNED_BYTE, nullptr));
    Unbind();
}

gl::Texture* gl::Texture::Load(const char* path) {
    Texture* texture = new Texture();

    int width, height, channels;
    uint8_t* data = stbi_load(path, &width, &height, &channels, 0);
    
    if (!data) { return nullptr; }

    Format format = Format::RGB;
    if (channels == 4) {
        format = Format::RGBA;
    }
    
    texture->Bind();
    GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, (uint32_t)format, width, height, 0, (uint32_t)format, GL_UNSIGNED_BYTE, data));
    GL_CALL(glGenerateMipmap(GL_TEXTURE_2D));
	
	GL_CALL(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLfloat)GL_REPEAT));
	GL_CALL(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLfloat)GL_REPEAT));
	
	GL_CALL(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLfloat)GL_LINEAR));
	GL_CALL(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLfloat)GL_LINEAR));
    texture->Unbind();

    stbi_image_free(data);

    return texture;
}