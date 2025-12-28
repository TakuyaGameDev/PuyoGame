#include "AnimationManager.h"

void AnimationManager::Add(const std::shared_ptr<AnimatedSprite>& sprite)
{
	sprites.push_back(sprite);
}

void AnimationManager::Update(float dt)
{
    for (auto& s : sprites)
    {
        s->Update(dt);
    }

    sprites.erase(
        std::remove_if(sprites.begin(), sprites.end(),
            [](const std::shared_ptr<AnimatedSprite>& s) { return s->IsFinish() && s->GetDestroyTimer() >= 30.0f; }),
        sprites.end()
    );
}

void AnimationManager::Draw(void) const
{
    for (auto& s : sprites) 
    {
        s->Draw();
    };
}

void AnimationManager::Clear(void)
{
}
