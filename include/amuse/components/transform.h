#pragma once

#include "amuse/ecs.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

class Transform : public ecs::Component {
public:
    Transform* parent = nullptr;

    glm::vec3 position = glm::vec3(0.0f);
    glm::quat rotation = glm::quat(glm::vec3(0.0f));
    glm::vec3 scale = glm::vec3(1.0f);

    glm::mat4 matrix;

    void Update() override;

    glm::mat4 GetModelMatrix();
};