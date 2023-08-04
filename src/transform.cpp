#include "transform.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

gl::Transform::Transform() : position(0.0f), rotation(1.0f, 0.0f, 0.0f, 0.0f), scale(1.0f) { }

gl::Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
    this->position = position;
    this->rotation = glm::quat(rotation);
    this->scale = scale;
}

glm::mat4 gl::Transform::GetModel() const {
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, position);
    model = model * glm::mat4_cast(rotation);
    model = glm::scale(model, scale);

    return model;
}