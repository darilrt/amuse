#pragma once

#include "amuse/mainfold.h"

#include <glm/glm.hpp>

namespace phx {
    class AABBCollider;

    class Collider {
    public:
        glm::vec3 center;

        virtual Mainfold Collide(Collider* other) = 0;

        virtual Mainfold Collide(AABBCollider* other) = 0;
    };

    class AABBCollider : public Collider {
    public:
        glm::vec3 extends;

        AABBCollider(glm::vec3 center, glm::vec3 extends);

        virtual Mainfold Collide(Collider* other) override;

        virtual Mainfold Collide(AABBCollider* other) override;
    };
}