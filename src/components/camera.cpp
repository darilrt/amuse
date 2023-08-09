#include "amuse/components/camera.h"
#include "amuse/singletons/screen.h"

#include <iostream>
#include <stdexcept>

gl::Camera* Camera::active = nullptr;

#define REQUIRE(type) if (!entity->HasComponent<type>()) { std::cout << "Required component " #type " not found\n"; abort(); }

void Camera::Init() {
    REQUIRE(Transform);

    transform = &entity->GetComponent<Transform>();

    active = new gl::Camera();
    active->SetOrthographic(2.0f, -1.0f, 1.0f);
    active->SetPosition({ 0.0f, 0.0f, 0.0f });
    Camera::active->SetViewport({ 0, 0, Screen::GetWidth(), Screen::GetHeight() });
    
    es::AddEventListener("Window Resize", [this](const es::Event& event) {
        this->active->SetViewport({ 0, 0, Screen::GetWidth(), Screen::GetHeight() });
    });
}

void Camera::Update() {
    Camera::active->position = transform->position;
    Camera::active->rotation = transform->rotation;
}

void Camera::SetScale(float scale) {
	Camera::active->SetOrthographic(scale, -1.0f, 1.0f);
}