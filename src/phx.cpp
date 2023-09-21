#include "amuse/phx.h"
#include "amuse/collider.h"

#include <glm/glm.hpp>

phx::Body::Body(Collider *collider, float mass) {
    this->collider = collider;
    this->velocity = glm::vec3(0, 0, 0);
    this->invMass = mass == 0 ? 0 : 1.0f / mass;
}

void phx::Body::ApplyForce(glm::vec3 force) {
    velocity += force * invMass;
}

phx::World::World() {
}

phx::World::~World() {
    bodies.clear();
}

void phx::World::Update(float dt) {
    for (int i = 0; i < bodies.size(); i++) {
        Body *body = bodies[i];
        body->collider->center += body->velocity * dt;
    }

    for (int i = 0; i < bodies.size(); i++) {
        Body *body = bodies[i];
        for (int j = i + 1; j < bodies.size(); j++) {
            Body *other = bodies[j];

            if (body->isStatic && other->isStatic) {
                continue;
            }

            Mainfold mainfold = body->collider->Collide(other->collider);

            if (mainfold.isColliding) {
                SolveCollision(*body, *other, mainfold);
            }
        }
    }
}

void phx::World::SolveCollision(Body& body, Body& other, Mainfold& mainfold) {
    if (body.isStatic) {
        other.collider->center -= mainfold.normal * mainfold.depth;
        return;
    }
    
    if (other.isStatic) {
        body.collider->center += mainfold.normal * mainfold.depth;
        return;
    }

    glm::vec3 relativeVelocity = body.velocity - other.velocity;
    float velocityAlongNormal = glm::dot(relativeVelocity, mainfold.normal);

    if (velocityAlongNormal > 0) {
        return;
    }

    
}

void phx::World::RemoveBody(Body *body) {
    for (int i = 0; i < bodies.size(); i++) {
        if (bodies[i] == body) {
            bodies.erase(bodies.begin() + i);
            return;
        }
    }
}

void phx::World::Clear() {
    bodies.clear();
}
