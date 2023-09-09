#ifdef _WIN32
#include <windows.h>
#endif

#include "amuse/camera.h"
#include "amuse/gldefs.h"
#include "amuse/camera.h"

#include <GL/glew.h>
#include <GL/gl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "amuse/camera.h"

void gl::Camera::SetPerspective(float fov, float _near, float _far) {
    this->fov = fov;
    this->_near = _near;
    this->_far = _far;

    projection = glm::perspective(glm::radians(fov), aspect, _near, _far);

    isOrthographic = false;
}

void gl::Camera::SetOrthographic(float scale, float _near, float _far) {
    this->scale = scale;
    this->_near = _near;
    this->_far = _far;

    projection = glm::ortho(-scale * aspect, scale * aspect, -scale, scale, _near, _far);

    isOrthographic = true;
}

void gl::Camera::SetViewport(const glm::vec4 &viewport) {
    this->viewport = viewport;
    this->aspect = viewport.z / viewport.w;

    if (isOrthographic) {
        SetOrthographic(scale, _near, _far);
    } else {
        SetPerspective(fov, _near, _far);
    }
}

glm::vec2 gl::Camera::ScreenToWorld2D(glm::vec2 screenPosition) {
    glm::vec2 worldPosition = glm::vec2(0.0f);
    glm::vec2 screenSize = glm::vec2(viewport.z, viewport.w);

    worldPosition.x = (screenPosition.x / screenSize.x) * 2.0f - 1.0f;
    worldPosition.y = (-screenPosition.y / screenSize.y) * 2.0f + 1.0f;
    worldPosition.x *= scale * aspect;
    worldPosition.y *= scale;
    
    return worldPosition + glm::vec2(position.x, position.y);
}

void gl::Camera::Begin() {
    view = glm::translate(glm::mat4_cast(rotation), -position);

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
