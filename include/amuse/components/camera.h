#pragma once

#include "amuse/ecs.h"
#include "amuse/gl.h"
#include "amuse/components/transform.h"

class Camera : public ecs::Component {
	Transform* transform = nullptr;

public:
	static gl::Camera* active;

	void Init() override;

	void Update() override;

	void SetScale(float scale);
};