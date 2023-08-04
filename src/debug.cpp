#include "debug.h"

static gl::WireBatch* wireBatch;

void debug::DrawLine(const glm::vec3 &start, const glm::vec3 &end, const glm::vec3 &color) {
    if (!wireBatch) { wireBatch = new gl::WireBatch(); }

    wireBatch->AddLine(start, end, color);
}

void debug::DrawCube(const glm::vec3 &position, const glm::vec3 &size, const glm::vec3 &color) {
    if (!wireBatch) { wireBatch = new gl::WireBatch(); }

    const glm::vec3 halfSize = size * 0.5f;
    const glm::vec3 min = position - halfSize;
    const glm::vec3 max = position + halfSize;

    wireBatch->AddLine(min, glm::vec3(min.x, min.y, max.z), color);
    wireBatch->AddLine(min, glm::vec3(min.x, max.y, min.z), color);
    wireBatch->AddLine(min, glm::vec3(max.x, min.y, min.z), color);
    wireBatch->AddLine(max, glm::vec3(max.x, max.y, min.z), color);
    wireBatch->AddLine(max, glm::vec3(max.x, min.y, max.z), color);
    wireBatch->AddLine(max, glm::vec3(min.x, max.y, max.z), color);
    wireBatch->AddLine(glm::vec3(min.x, max.y, min.z), glm::vec3(max.x, max.y, min.z), color);
    wireBatch->AddLine(glm::vec3(min.x, max.y, min.z), glm::vec3(min.x, max.y, max.z), color);
    wireBatch->AddLine(glm::vec3(max.x, min.y, min.z), glm::vec3(max.x, max.y, min.z), color);
    wireBatch->AddLine(glm::vec3(max.x, min.y, min.z), glm::vec3(max.x, min.y, max.z), color);
    wireBatch->AddLine(glm::vec3(min.x, min.y, max.z), glm::vec3(max.x, min.y, max.z), color);
    wireBatch->AddLine(glm::vec3(min.x, min.y, max.z), glm::vec3(min.x, max.y, max.z), color);
    
}

void debug::DrawBounds(const math::Bounds &bounds, const glm::vec3 &color) {
    if (!wireBatch) { wireBatch = new gl::WireBatch(); }

    const glm::vec3 min = bounds.GetMax();
    const glm::vec3 max = bounds.GetMin();

    wireBatch->AddLine(min, glm::vec3(min.x, min.y, max.z), color);
    wireBatch->AddLine(min, glm::vec3(min.x, max.y, min.z), color);
    wireBatch->AddLine(min, glm::vec3(max.x, min.y, min.z), color);
    wireBatch->AddLine(max, glm::vec3(max.x, max.y, min.z), color);
    wireBatch->AddLine(max, glm::vec3(max.x, min.y, max.z), color);
    wireBatch->AddLine(max, glm::vec3(min.x, max.y, max.z), color);
    wireBatch->AddLine(glm::vec3(min.x, max.y, min.z), glm::vec3(max.x, max.y, min.z), color);
    wireBatch->AddLine(glm::vec3(min.x, max.y, min.z), glm::vec3(min.x, max.y, max.z), color);
    wireBatch->AddLine(glm::vec3(max.x, min.y, min.z), glm::vec3(max.x, max.y, min.z), color);
    wireBatch->AddLine(glm::vec3(max.x, min.y, min.z), glm::vec3(max.x, min.y, max.z), color);
    wireBatch->AddLine(glm::vec3(min.x, min.y, max.z), glm::vec3(max.x, min.y, max.z), color);
    wireBatch->AddLine(glm::vec3(min.x, min.y, max.z), glm::vec3(min.x, max.y, max.z), color);
}

void debug::Draw(gl::Camera &camera) {
    if (!wireBatch) { return; }

    wireBatch->Bake();
    wireBatch->Draw(camera);
    wireBatch->Clear();
}