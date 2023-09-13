#pragma once

#include <glm/glm.hpp>

namespace phx {

    class Body;

    struct Mainfold {
        Body* bodyA;
        Body* bodyB;
        glm::vec3 normal;
        float depth;
        bool isColliding;
    };
}