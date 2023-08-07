#pragma once

#include "amuse/gl.h"
#include "amuse/components/transform.h"

class Sprite : public ecs::Component {
    static gl::Shader* shader;
    static gl::Mesh* mesh;

    Transform* transform = nullptr;
    gl::Texture* texture = nullptr;
    glm::vec2 origin = glm::vec2(0.5f);
    glm::ivec2 index = glm::ivec2(0);
    float aspect = 1.0f;
    glm::vec2 size = glm::vec2(1.0f);

public:
    void Init() override;

    void Render() override;

    inline void SetTexture(gl::Texture& texture) { this->texture = &texture; }

    inline void SetOrigin(glm::vec2 origin) { this->origin = origin; }

    inline void SetIndex(glm::ivec2 index) { this->index = index; }

    void SetSpriteSize(glm::ivec2 size);

    inline glm::vec2 GetOrigin() const { return origin; }

    inline glm::ivec2 GetIndex() const { return index; }

    inline glm::ivec2 GetSize() const { return size; }

    inline gl::Texture& GetTexture() const { return *texture; }
};