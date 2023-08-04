#include "camera.h"
#include "gldefs.h"

#include <windows.h>
#include <GL/glew.h>
#include <GL/gl.h>

void gl::Camera::SetPerspective(float fov, float aspect, float _near, float _far) {
    this->fov = fov;
    this->aspect = aspect;
    this->_near = _near;
    this->_far = _far;

    projection = glm::perspective(glm::radians(fov), aspect, _near, _far);
}

void gl::Camera::SetOrthographic(float scale, float _near, float f_ar) {
    this->scale = scale;
    this->_near = _near;
    this->_far = _far;

    projection = glm::ortho(-scale, scale, -scale, scale, _near, _far);
}

void gl::Camera::Begin() {
    view = glm::translate(glm::mat4_cast(rotation), position);

    if (renderTexture != nullptr) {
        renderTexture->Bind();
    }

	GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	GL_CALL(glEnable(GL_CULL_FACE));
	GL_CALL(glEnable(GL_DEPTH_TEST));

	GL_CALL(glEnable(GL_TEXTURE_2D));

	GL_CALL(glEnable(GL_ALPHA_TEST));
	GL_CALL(glEnable(GL_BLEND));
	GL_CALL(glAlphaFunc(GL_GREATER, 0.5));
	GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

void gl::Camera::End() {
}