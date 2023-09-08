
#include "amuse/components/transform.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

void Transform::Update() {
    matrix = glm::mat4(1.0f);
    matrix = glm::translate(matrix, position);
    matrix = glm::scale(matrix, scale);
    matrix = glm::mat4_cast(rotation) * matrix;

    if (parent != nullptr) {
        matrix = parent->matrix * matrix;
    }
}

glm::mat4 Transform::GetModelMatrix() {
    Update();
    return matrix;
}