#pragma once
#include <functional>
#include <string>
#include <vector>
#include "../../UIElement.h"

using StateCallback = std::function<void()>;

class TitleObject : public UIElement {
public:
    TitleObject(AnimationManager& animManager, const UITYPE& type, const std::vector<int>& handles, const Vector2& pos);
    ~TitleObject();

    void Update(float dt);
    void Draw(void) const;

    void SetCanMove(bool flg)
    {
        this->canMove = flg;
    }

    void SetOnBreakEnd(StateCallback cb) { onBreakEnd = cb; }

private:
    void Move(int speed,int range);

    StateCallback onBreakEnd = nullptr;

    std::vector<int> handles;
    std::string text;

    Vector2 moveRange;
    bool canMove;

    std::shared_ptr<AnimatedSprite> sprite;
};