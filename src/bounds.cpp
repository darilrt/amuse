#include "bounds.h"

math::Bounds::Bounds() : center(0.0f), size(0.0f), extends(0.0f), min(0.0f), max(0.0f) { }

math::Bounds::Bounds(glm::vec3 center, glm::vec3 size) : center(center), size(size) {
    extends = size * 0.5f;
    min = center - extends;
    max = center + extends;
}

bool math::Bounds::Intersect(Bounds& bounds) {
    return (min.x <= bounds.max.x && max.x >= bounds.min.x) &&
           (min.y <= bounds.max.y && max.y >= bounds.min.y) &&
           (min.z <= bounds.max.z && max.z >= bounds.min.z);
}

void math::Bounds::SetCenter(glm::vec3 center) {
    this->center = center;
    min = center - extends;
    max = center + extends;
    size = extends * 2.0f;
}

void math::Bounds::SetSize(glm::vec3 size) {
    this->size = size;
    extends = size * 0.5f;
    min = center - extends;
    max = center + extends;
}

void math::Bounds::SetMin(glm::vec3 min) {
    this->min = min;
    extends = max - min;
    center = min + extends * 0.5f;
    size = extends * 2.0f;
}

void math::Bounds::SetMax(glm::vec3 max) {
    this->max = max;
    extends = max - min;
    center = min + extends * 0.5f;
    size = extends * 2.0f;
}

void math::Bounds::SetExtends(glm::vec3 extends) { 
    this->extends = extends;
    min = center - extends;
    max = center + extends;
    size = extends * 2.0f;
}

void math::Bounds::Expand(glm::vec3 point) {
    min = glm::min(min, point);
    max = glm::max(max, point);
    extends = max - min;
    center = min + extends * 0.5f;
    size = extends * 2.0f;
}

