#include <DxLib.h>
#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite():animType(ANIM_TYPE::IDLE)
{
}

AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::SetAnim(const ANIM_TYPE& type)
{
    if (animType == type)
    {
        return;
    }
    isFinish = false;
    animType = type;
    frameIndex = 0;
    timer = 0.0f;
}

void AnimatedSprite::SetPos(const Vector2& pos)
{
    this->pos = pos;
}

void AnimatedSprite::SetScale(float scale)
{
    this->scale = scale;
}

void AnimatedSprite::SetRotation(float rot)
{
    this->rotation = rot;
}

void AnimatedSprite::SetAnimMap(const ANIM_TYPE& type, const std::vector<int>& frames, float interval, bool loop)
{
    animMap[type] = AnimData{ frames, interval, loop };
}

void AnimatedSprite::Update(float dt)
{
    if (isFinish)
    {
        destroyTimer += dt;
        return;
    }

    auto it = animMap.find(animType);
    if (it == animMap.end() || it->second.frames.empty())
    {
        return;
    }

    AnimData& data = it->second;

    timer += dt;
    if (timer < data.interval)
    {
        return;
    }
    timer = 0.0f;

    frameIndex++;

    if (frameIndex >= (int)data.frames.size()) 
    {
        if (data.loop)
        {
            frameIndex = 0;
        }
        else 
        {
            frameIndex = (int)data.frames.size() - 1;
            isFinish = true;
            destroyTimer = 0.0f;
        }
    }
}

void AnimatedSprite::Draw(void) const
{
    if (destroyTimer < 30.0f)
    {
        auto it = animMap.find(animType);
        if (it == animMap.end() || it->second.frames.empty())
        {
            return;
        }
        // ’†S‚ðŠî€‚É‰ñ“]EŠg‘å•`‰æ
        DrawRotaGraph(pos.x, pos.y, scale, rotation, it->second.frames[frameIndex],true);
    }
}
