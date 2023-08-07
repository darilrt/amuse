
#include "amuse/components/transform.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

void Transform::Update() {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    model = glm::mat4_cast(rotation) * model;

    if (parent != nullptr) {
        model = parent->matrix * model;
    }

    this->matrix = model;
}