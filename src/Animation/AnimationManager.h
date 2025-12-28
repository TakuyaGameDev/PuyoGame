#pragma once
#include <vector>
#include <memory>
#include <algorithm>
#include "AnimatedSprite.h"

class AnimationManager {
public:
	void Add(const std::shared_ptr<AnimatedSprite>& sprite);

	void Update(float dt);

	void Draw(void) const;

	void Clear(void);
private:
	std::vector<std::shared_ptr<AnimatedSprite>> sprites;
};