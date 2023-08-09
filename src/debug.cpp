#include "amuse/debug.h"

#include "amuse/core.h"
#include "amuse/debug.h"

#include <iostream>

static gl::WireBatch* wireBatch;
static gl::WireBatch* staticWireBatch;

void debug::Log(const std::string& message) {
    std::cout << message << std::endl;
}

void debug::Init(wm::Window* window) {
    
#ifdef AMUSE_USE_IMGUI
#ifdef __APPLE__
	// GL 3.2 Core + GLSL 150
	const char* glsl_version = "#version 150";
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui_ImplSDL2_InitForOpenGL(window->window, window->context);
	ImGui_ImplOpenGL3_Init();
#endif

}

void debug::DrawLine(const glm::vec3 &start, const glm::vec3 &end, const glm::vec3 &color) {
    if (!wireBatch) { wireBatch = new gl::WireBatch(); }

    wireBatch->AddLine(start, end, color);
}

void debug::DrawCube(const glm::vec3 &position, const glm::vec3 &size, const glm::vec3 &color) {
    if (!wireBatch) { wireBatch = new gl::WireBatch(); }

    const glm::vec3 halfSize = size * 0.5f;
    const glm::vec3 min = position - halfSize;
    const glm::vec3 max = position + halfSize;

    wireBatch->AddLine(min, glm::vec3(min.x, min.y, max.z), color);
    wireBatch->AddLine(min, glm::vec3(min.x, max.y, min.z), color);
    wireBatch->AddLine(min, glm::vec3(max.x, min.y, min.z), color);
    wireBatch->AddLine(max, glm::vec3(max.x, max.y, min.z), color);
    wireBatch->AddLine(max, glm::vec3(max.x, min.y, max.z), color);
    wireBatch->AddLine(max, glm::vec3(min.x, max.y, max.z), color);
    wireBatch->AddLine(glm::vec3(min.x, max.y, min.z), glm::vec3(max.x, max.y, min.z), color);
    wireBatch->AddLine(glm::vec3(min.x, max.y, min.z), glm::vec3(min.x, max.y, max.z), color);

    wireBatch->AddLine(glm::vec3(max.x, min.y, min.z), glm::vec3(max.x, max.y, min.z), color);
    wireBatch->AddLine(glm::vec3(max.x, min.y, min.z), glm::vec3(max.x, min.y, max.z), color);
    wireBatch->AddLine(glm::vec3(min.x, min.y, max.z), glm::vec3(max.x, min.y, max.z), color);
    wireBatch->AddLine(glm::vec3(min.x, min.y, max.z), glm::vec3(min.x, max.y, max.z), color);
    
}

void debug::DrawBounds(const math::Bounds &bounds, const glm::vec3 &color) {
    if (!wireBatch) { wireBatch = new gl::WireBatch(); }

    const glm::vec3 min = bounds.GetMax();
    const glm::vec3 max = bounds.GetMin();

    wireBatch->AddLine(min, glm::vec3(min.x, min.y, max.z), color);
    wireBatch->AddLine(min, glm::vec3(min.x, max.y, min.z), color);
    wireBatch->AddLine(min, glm::vec3(max.x, min.y, min.z), color);
    wireBatch->AddLine(max, glm::vec3(max.x, max.y, min.z), color);
    wireBatch->AddLine(max, glm::vec3(max.x, min.y, max.z), color);
    wireBatch->AddLine(max, glm::vec3(min.x, max.y, max.z), color);
    wireBatch->AddLine(glm::vec3(min.x, max.y, min.z), glm::vec3(max.x, max.y, min.z), color);
    wireBatch->AddLine(glm::vec3(min.x, max.y, min.z), glm::vec3(min.x, max.y, max.z), color);
    wireBatch->AddLine(glm::vec3(max.x, min.y, min.z), glm::vec3(max.x, max.y, min.z), color);
    wireBatch->AddLine(glm::vec3(max.x, min.y, min.z), glm::vec3(max.x, min.y, max.z), color);
    wireBatch->AddLine(glm::vec3(min.x, min.y, max.z), glm::vec3(max.x, min.y, max.z), color);
    wireBatch->AddLine(glm::vec3(min.x, min.y, max.z), glm::vec3(min.x, max.y, max.z), color);
}

void debug::DrawBounds(const math::Bounds2D &bounds, const glm::vec3 &color) {
    if (!wireBatch) { wireBatch = new gl::WireBatch(); }

    const glm::vec2 min = bounds.GetMax();
    const glm::vec2 max = bounds.GetMin();

    wireBatch->AddLine(glm::vec3(min.x, min.y, 0.0f), glm::vec3(min.x, max.y, 0.0f), color);
    wireBatch->AddLine(glm::vec3(min.x, min.y, 0.0f), glm::vec3(max.x, min.y, 0.0f), color);
    wireBatch->AddLine(glm::vec3(max.x, max.y, 0.0f), glm::vec3(max.x, min.y, 0.0f), color);
    wireBatch->AddLine(glm::vec3(max.x, max.y, 0.0f), glm::vec3(min.x, max.y, 0.0f), color);
}

void debug::Draw(gl::Camera &camera) {
    if (wireBatch) {
        wireBatch->Bake();
        wireBatch->Draw(camera);
        wireBatch->Clear();
    }
    
    if (staticWireBatch) {
        staticWireBatch->Draw(camera);
    }
}

void debug::InitFrame() {
#ifdef AMUSE_USE_IMGUI
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
#endif
}

void debug::DrawStaticLine(const glm::vec3 &start, const glm::vec3 &end, const glm::vec3 &color) {
    if (!staticWireBatch) { staticWireBatch = new gl::WireBatch(); }

    staticWireBatch->AddLine(start, end, color);

    staticWireBatch->Bake();
}

void debug::DrawStaticGrid(const glm::vec3 &position, const glm::vec3 &size, const glm::vec3 &color) {
    if (!staticWireBatch) { staticWireBatch = new gl::WireBatch(); }

    const glm::vec3 halfSize = size * 0.5f;
    const glm::vec3 min = position - halfSize;
    const glm::vec3 max = position + halfSize;

    for (float x = min.x; x <= max.x; x += 1.0f) {
        staticWireBatch->AddLine(glm::vec3(x, min.y, min.z), glm::vec3(x, max.y, min.z), color);
    }

    for (float y = min.y; y <= max.y; y += 1.0f) {
        staticWireBatch->AddLine(glm::vec3(min.x, y, min.z), glm::vec3(max.x, y, min.z), color);
    }

    staticWireBatch->Bake();
}

void debug::DrawGui() {
#ifdef AMUSE_USE_IMGUI
	ImGui::Begin("Debug");
	ImGui::Text("FPS: %f", 1.0f / Input::DeltaTime());
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif
}