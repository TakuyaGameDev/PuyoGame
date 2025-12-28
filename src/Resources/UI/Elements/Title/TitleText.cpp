#include <DxLib.h>
#include <algorithm>
#include "TitleText.h"
#include "../../../../Common/Application.h"
#include "TitleObject.h"

TitleText::TitleText(const UITYPE& type, int font, const Vector2& pos, const unsigned int& col, const std::string& text) : font(font), UIElement(type, pos)
{
    size.x = GetDrawStringWidthToHandle(text.c_str(), strlen(text.c_str()), font);
    size.y = GetFontSizeToHandle(font);
    this->text = text;
    this->color = col;

    auto scrSize = Application::GetInstance().GetScreenSize();
    moveRange = { 0, scrSize.y / 2 - (size.y / 2) };

    switch (type)
    {
    case UITYPE::TITLE_1:
        updateFunc = [this](int range){ 
            Move(2, range); 
        };
        edgeColor = GetColor(255, 220, 100);
        break;
    case UITYPE::TITLE_2:
        updateFunc = [this](int range) {
            Move(-2, range);
        };
        edgeColor = GetColor(255, 220, 100);
        break;
    case UITYPE::TITLE_7:
    case UITYPE::TITLE_8:
    case UITYPE::TITLE_9:
        edgeColor = GetColor(255, 100, 0);
        this->pos = { scrSize.x / 2 - (size.x / 2), pos.y };
        break;
    default:
        updateFunc = nullptr;
        break;
    }
}

TitleText::~TitleText()
{
}

void TitleText::Update(float dt)
{
    if (updateFunc) {
        updateFunc(moveRange.y);
    }
}

void TitleText::Draw() const
{
    int alpha = 180 + (int)(sin(GetNowCount() * 0.005f) * 50);
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

    DrawStringToHandle(pos.x, pos.y, text.c_str(), color, font, edgeColor);

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void TitleText::Move(int speed, int range)
{
    switch (type)
    {
    case UITYPE::TITLE_1:
        pos.y = min(pos.y + speed, range);
        if (pos.y >= range)
        {
            // 定位置に来たらコールバック関数を呼び出して
            if (onReachPosition)
            {
                onReachPosition();
            }
            // 1度しか呼び出さない為中を空にする
            onReachPosition = nullptr;
        }
        break;
    case UITYPE::TITLE_2:
        pos.y = max(pos.y + speed, range);
        break;
    }
}
