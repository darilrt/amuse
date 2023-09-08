#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace gl { 

    class Transform {
    public:
        glm::vec3 position;
        glm::quat rotation;
        glm::vec3 scale;

        Transform();
        Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

        glm::mat4 GetModel() const;

        inline void Translate(glm::vec3 translation) { position += translation; }
        
        inline void Rotate(glm::vec3 rotation) { this->rotation = glm::quat(rotation) * this->rotation;}

        inline void Scale(glm::vec3 scale) { this->scale *= scale; }
    };

}
