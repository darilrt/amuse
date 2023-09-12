#pragma once

#include "amuse/gl.h"
#include "amuse/wm.h"
#include "amuse/es.h"
#include "amuse/ecs.h"
#include "amuse/primitives.h"
#include "amuse/bounds.h"
#include "amuse/components.h"
#include "amuse/singletons.h"
#include "amuse/file.h"

#ifdef _DEBUG
#include "amuse/debug.h"
#endif

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace amuse {
    void Init(int width, int height);
    void RunGame();
}