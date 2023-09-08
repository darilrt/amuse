#pragma once

#include "amuse/ecs.h"
#include "amuse/gl.h"
#include "amuse/components/transform.h"

class Camera : public ecs::Component {
	Transform* transform = nullptr;
	gl::Camera camera;

public:
	static gl::Camera* active;

	void Init() override;

	void Update() override;

	void SetScale(float scale);

	void SetPerspective(float fov, float near, float far);

	void SetOrthographic(float scale);

	void SetActive();

	inline glm::mat4 GetViewMatrix() const { return camera.GetView(); }
};