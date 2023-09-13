#include "amuse/collider.h"

phx::AABBCollider::AABBCollider(glm::vec3 center, glm::vec3 extends) {
    this->center = center;
    this->extends = extends;
}

phx::Mainfold phx::AABBCollider::Collide(Collider *other) {
    return Mainfold();
}

phx::Mainfold phx::AABBCollider::Collide(AABBCollider *other) {
    Mainfold mainfold;
    mainfold.bodyA = nullptr;
    mainfold.bodyB = nullptr;
    mainfold.isColliding = false;

    glm::vec3 distance = other->center - this->center;

    // Overlap on axies
    float x_overlap = this->extends.x + other->extends.x - abs(distance.x);

    if (x_overlap <= 0) { return mainfold; }

    float y_overlap = this->extends.y + other->extends.y - abs(distance.y);

    if (y_overlap <= 0) { return mainfold; }

    float z_overlap = this->extends.z + other->extends.z - abs(distance.z);

    if (z_overlap <= 0) { return mainfold; }

    // Find axis of least depth

    if (x_overlap < y_overlap && x_overlap < z_overlap) {
        mainfold.normal = glm::vec3(distance.x > 0 ? 1 : -1, 0, 0);
        mainfold.depth = x_overlap;
    } else if (y_overlap < x_overlap && y_overlap < z_overlap) {
        mainfold.normal = glm::vec3(0, distance.y > 0 ? 1 : -1, 0);
        mainfold.depth = y_overlap;
    } else {
        mainfold.normal = glm::vec3(0, 0, distance.z > 0 ? 1 : -1);
        mainfold.depth = z_overlap;
    }

    mainfold.isColliding = true;

    return mainfold;
}
