#pragma once
#include <map>
#include <vector>
#include <string>
#include "AnimType.h"
#include "../Common/Vector2.h"

struct AnimData {
	std::vector<int> frames; // フレームハンドル
	float interval = 1.0f;   // フレーム切り替え間隔
	bool loop = true;        // ループするか
};

class AnimatedSprite {
public:
	AnimatedSprite();
	~AnimatedSprite();

	void SetAnim(const ANIM_TYPE& type);

	void SetPos(const Vector2& pos);

	void SetScale(float scale);

	void SetRotation(float rot);

	void SetAnimMap(const ANIM_TYPE& type, const std::vector<int>& frames, float interval = 1.0f, bool loop = true);

	void Update(float dt);

	void Draw(void) const;

	const bool& IsFinish(void) const
	{
		return isFinish;
	}

	const float& GetDestroyTimer(void) const
	{
		return destroyTimer;
	}

private:
	bool isFinish = false;
	ANIM_TYPE animType;
	Vector2 pos;
	float timer = 0.0f;
	float destroyTimer = 0.0f;
	int frameIndex = 0;
	float scale = 1.0f;
	float rotation = 0.0f;
	std::map<ANIM_TYPE, AnimData> animMap;
};