#include "amuse/core.h"

void SpriteAnimator::Init() {
    sprite = &entity->GetComponent<Sprite>();

    assert(sprite != nullptr, "Only entities with a Sprite component can have a SpriteAnimator component");
}

void SpriteAnimator::Update() {
    if (currentAnimation) {
        currentAnimation->time += Input::DeltaTime();
        if (currentAnimation->time >= currentAnimation->frameTime) {
            currentAnimation->time = 0.0f;
            currentAnimation->index++;
            if (currentAnimation->index >= currentAnimation->frames.size()) {
                currentAnimation->index = 0;
            }
            sprite->SetIndex(currentAnimation->frames[currentAnimation->index]);
        }
    }
}

void SpriteAnimator::AddAnimation(const std::string &name, const std::vector<glm::ivec2> &frames, float frameTime) {
    animations[name] = { frames, frameTime };
}

void SpriteAnimator::Play(const std::string &name) {
    if (currentAnimation == &animations[name]) return;

    currentAnimation = &animations[name];
    currentAnimation->index = 0;
    currentAnimation->time = 0.0f;
    sprite->SetIndex(currentAnimation->frames[currentAnimation->index]);
}
