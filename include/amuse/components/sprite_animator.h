#pragma once

#include "amuse/components/sprite.h"

#include <unordered_map>
#include <vector>

class SpriteAnimator : public ecs::Component {
    struct Animation {
        std::vector<glm::ivec2> frames;
        float frameTime;
        float time = 0.0f;
        int32_t index = 0;
    };

    std::unordered_map<std::string, Animation> animations;
    Animation* currentAnimation = nullptr;

    Sprite* sprite = nullptr;

public:
    void Init() override;

    void Update() override;

    void AddAnimation(const std::string& name, const std::vector<glm::ivec2>& frames, float frameTime);

    void Play(const std::string& name);
};
