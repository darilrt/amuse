#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "amuse/collider.h"

namespace phx {

    class Body {
    public:
        Collider* collider;
        glm::vec3 velocity;
        float invMass;

        bool isStatic;
        bool isKinematic;

        Body(Collider* collider, float mass=1.0f);

        void ApplyForce(glm::vec3 force);
    };

    class World {
    public:
        std::vector<Body*> bodies;

        World();
        ~World();

        void Update(float dt);

        inline void AddBody(Body* body) {
            bodies.push_back(body);
        }

        void SolveCollision(Body& body, Body& other, Mainfold& mainfold);

        void RemoveBody(Body* body);

        void Clear();
    };

}