#pragma once

#include "amuse/mesh.h"
#include "amuse/shader.h"
#include "amuse/buffer.h"
#include "amuse/texture.h"
#include "amuse/camera.h"
#include "amuse/transform.h"
#include "amuse/draw.h"

#include <cstdint>

namespace gl {
	class Mesh;
	class Shader;
	class Camera;
	class Transform;

	extern bool initialized;

	void Init();

	void Clear();

	void Draw(Mesh *mesh, gl::Shader *shader, gl::Transform &transform, gl::Camera &camera);
}
