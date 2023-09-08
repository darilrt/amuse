#include "amuse/core.h"

#include <iostream>
#include <stdexcept>

gl::Camera* Camera::active = nullptr;

void Camera::Init() {
    REQUIRE_COMPONENT(Transform);

    transform = &entity->GetComponent<Transform>();

    camera.SetOrthographic(2.0f, -1.0f, 1.0f);
    camera.SetViewport({ 0, 0, Screen::GetWidth(), Screen::GetHeight() });
    
    es::AddEventListener("Window Resize", [this](const es::Event& event) {
        this->active->SetViewport({ 0, 0, Screen::GetWidth(), Screen::GetHeight() });
    });
}

void Camera::Update() {
    camera.position = transform->position;
    camera.rotation = transform->rotation;
}

void Camera::SetPerspective(float fov, float near, float far) {
    camera.SetPerspective(fov, near, far);
}

void Camera::SetOrthographic(float scale) {
    camera.SetOrthographic(scale, -1.0f, 1.0f);
}

void Camera::SetActive() {
    Camera::active = &camera;
}