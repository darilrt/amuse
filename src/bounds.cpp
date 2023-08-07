#include "amuse/bounds.h"
#include "amuse/bounds.h"

math::Bounds::Bounds() : center(0.0f), size(0.0f), extends(0.0f), min(0.0f), max(0.0f) { }

math::Bounds::Bounds(glm::vec3 center, glm::vec3 size) : center(center), size(size) {
    extends = size * 0.5f;
    min = center - extends;
    max = center + extends;
}

bool math::Bounds::Intersects(Bounds& bounds) {
    return (min.x <= bounds.max.x && max.x >= bounds.min.x) &&
           (min.y <= bounds.max.y && max.y >= bounds.min.y) &&
           (min.z <= bounds.max.z && max.z >= bounds.min.z);
}

bool math::Bounds::Contains(glm::vec3 point) {
    return (point.x >= min.x && point.x <= max.x &&
        point.y >= min.y && point.y <= max.y &&
        point.z >= min.z && point.z <= max.z);
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

math::Bounds2D::Bounds2D() {
    min = glm::vec2(0.0f);
    max = glm::vec2(0.0f);
    extends = glm::vec2(0.0f);
    center = glm::vec2(0.0f);
    size = glm::vec2(0.0f);
}

math::Bounds2D::Bounds2D(glm::vec2 center, glm::vec2 size) : center(center), size(size) {
    extends = size * 0.5f;
    min = center - extends;
    max = center + extends;
}

bool math::Bounds2D::Intersects(Bounds2D& bounds) {
    return (min.x <= bounds.max.x && max.x >= bounds.min.x) &&
           (min.y <= bounds.max.y && max.y >= bounds.min.y);
}

bool math::Bounds2D::Contains(glm::vec2 point) {
    return (point.x >= min.x && point.x <= max.x &&
        point.y >= min.y && point.y <= max.y);
}

void math::Bounds2D::SetCenter(glm::vec2 center) {
    this->center = center;
    min = center - extends;
    max = center + extends;
    size = extends * 2.0f;
}

void math::Bounds2D::SetSize(glm::vec2 size) {
    this->size = size;
    extends = size * 0.5f;
    min = center - extends;
    max = center + extends;
}

void math::Bounds2D::SetMin(glm::vec2 min) {
    this->min = min;
    extends = max - min;
    center = min + extends * 0.5f;
    size = extends * 2.0f;
}

void math::Bounds2D::SetMax(glm::vec2 max) {
    this->max = max;
    extends = max - min;
    center = min + extends * 0.5f;
    size = extends * 2.0f;
}

void math::Bounds2D::SetExtends(glm::vec2 extends) {
    this->extends = extends;
    min = center - extends;
    max = center + extends;
    size = extends * 2.0f;
}

void math::Bounds2D::Expand(glm::vec2 point) {
    min = glm::min(min, point);
    max = glm::max(max, point);
    extends = max - min;
    center = min + extends * 0.5f;
    size = extends * 2.0f;
}