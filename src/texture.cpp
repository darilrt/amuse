#include "amuse/texture.h"
#include "amuse/gldefs.h"

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "amuse/stb_image.h"

#include <windows.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <cstdint>
#include <iostream>

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
    
    if (!data) { 
        std::cout << "Failed to load texture: " << path << std::endl;
        delete texture;
        return nullptr;
    }

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

    texture->format = format;
    texture->width = width;
    texture->height = height;

    return texture;
}

void gl::Texture::SetFilter(Filter filter) {
    Bind();
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (GLint)filter));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (GLint)filter));
    Unbind();
}