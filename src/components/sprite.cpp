#include "amuse/core.h"

#include <glm/gtc/type_ptr.hpp>

gl::Shader* Sprite::shader = nullptr;
gl::Mesh* Sprite::mesh = nullptr;

void Sprite::Init() {
    if (!shader) shader = &Assets::Get<gl::Shader>("shaders/sprite");
    if (!mesh) mesh = primitive::CreateQuad();

    transform = &entity->GetComponent<Transform>();

    assert(transform != nullptr, "Only entities with a Transform component can have a Sprite component");
    
    es::AddEventListener("Tick", [this](const es::Event& event) {
        this->shader->Reload();
    });
}

void Sprite::Render() {
    shader->Bind();
    shader->SetCameraUniforms(*Camera::active);
    shader->SetUniformMatrix4fv(SHADER_UNIFORM_MODEL, glm::value_ptr(transform->matrix));

    if (texture) {
        shader->SetSampler2D("spriteTexture", texture);
        shader->SetUniform2f("spriteSize", size.x, size.y);
        shader->SetUniform2f("spriteOrigin", origin.x, origin.y);
        shader->SetUniform1f("spriteAspect", aspect);
        shader->SetUniform2i("spriteIndex", index.x, index.y);
    }

    mesh->DrawTriangles();
    shader->Unbind();
}

void Sprite::SetSpriteSize(glm::ivec2 size) {
    this->size = glm::vec2(size) / glm::vec2(texture->GetSize());
    this->aspect = size.x / (float)size.y;
}