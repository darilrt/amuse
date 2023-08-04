#pragma once

#include "mesh.h"
#include "shader.h"
#include "buffer.h"
#include "texture.h"
#include "camera.h"
#include "transform.h"
#include "draw.h"

#include <cstdint>

namespace gl {
	extern bool initialized;

	void Init();

	void Clear();
}
