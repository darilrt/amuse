#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <SDL.h>
#include <iostream>

#include "amuse/gl.h"
#include "amuse/gldefs.h"
#include "amuse/gl.h"

bool gl::initialized = false;

void gl::Init() {
	if (gl::initialized) { return; }

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	uint32_t err = glewInit();
	if (GLEW_OK != err) {
		std::cout << "Error: " << glewGetErrorString(err) << std::endl;
		exit(1);
	}

	GL_CALL(glClearColor(0.05f, 0.05f, 0.05f, 1.0f));

	gl::initialized = true;
}

void gl::Clear() {
	GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	GL_CALL(glEnable(GL_CULL_FACE));
	GL_CALL(glEnable(GL_DEPTH_TEST));

	GL_CALL(glEnable(GL_TEXTURE_2D));

	GL_CALL(glEnable(GL_ALPHA_TEST));
	GL_CALL(glEnable(GL_BLEND));
	GL_CALL(glAlphaFunc(GL_GREATER, 0.5));
	GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

void gl::Draw(Mesh *mesh, Shader *shader, Transform &transform, Camera &camera) {
	shader->Bind();
	shader->SetCameraUniforms(camera);
	shader->SetModelTransform(transform);
	mesh->DrawTriangles();
	shader->Unbind();
}