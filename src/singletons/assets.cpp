
#include "amuse/singletons/assets.h"

#include <string>

std::string Assets::basePath = "";

void Assets::Init(const std::string& basePath) {
    Assets::basePath = basePath;
}