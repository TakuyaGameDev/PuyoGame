#pragma once
#include <string>
#include "../../UIElement.h"

class TitleText : public UIElement {
public:
    TitleText(const UITYPE& type, int font, const Vector2& pos, const unsigned int& col, const std::string& text);
    ~TitleText();

    void Update(float dt);
    void Draw() const;

private:
    void Move(int speed, int range);

    int font;
    std::string text;
    unsigned int color;
    unsigned int edgeColor;
    Vector2 moveRange;
};