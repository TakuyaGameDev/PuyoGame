#pragma once
#include <functional>
#include "../../Common/Vector2.h"
#include "../../Resources/UI/UIType.h"
#include "../../Animation/AnimationManager.h"

using UpdateFunc = std::function<void(int)>;

class UIElement {
public:
    UIElement(const UITYPE& type, const Vector2& pos, AnimationManager* animManager = nullptr) :type(type), pos(pos), animManager(animManager){}
    virtual ~UIElement() = default;
    virtual void Update(float dt) {}
    virtual void Draw() const {}

    const UIElement& GetByType(const UITYPE& type) const
    {
        if (this->type == type)
        {
            return *this;
        }
    }

    /// <summary>
    /// テキストが定位置に来たら宝箱オブジェクトを落とすコールバック関数
    /// </summary>
    /// <param name="cb">設定するコールバック関数</param>
    void SetOnReachPosition(std::function<void()> cb) { onReachPosition = cb; }

    virtual const bool& CanShiftNext(void) const { return false; };

    bool visible = true;
protected:
    UpdateFunc updateFunc = nullptr;
    std::function<void()> onReachPosition = nullptr;

    UITYPE type;
    Vector2 pos;
    Vector2 size = { 0,0 };
    AnimationManager* animManager;
};