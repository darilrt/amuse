#pragma once

#include "amuse/core.h"

class MeshRenderer : public ecs::Component {
	Transform* transform;
	gl::Mesh* mesh;
	gl::Shader* shader;

public:
	void Init() override;

	void Render() override;

	inline void SetMesh(gl::Mesh* mesh) {
		this->mesh = mesh;
	}

	inline gl::Mesh& GetMesh() {
		return *mesh;
	}

	inline void SetShader(gl::Shader* shader) {
		this->shader = shader;
	}
};

