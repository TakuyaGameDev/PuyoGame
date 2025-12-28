#include <DxLib.h>
#include <algorithm>
#include "../../../../Common/Application.h"
#include "TitleObject.h"

TitleObject::TitleObject(AnimationManager& animManager, const UITYPE& type, const std::vector<int>& handles, const Vector2& pos) : handles(handles), UIElement(type, pos, &animManager)
{
	canMove = false;
	auto scrSize = Application::GetInstance().GetScreenSize();
	moveRange = { 0, scrSize.y / 2 - (size.y / 2) };
	if (type == UITYPE::TITLE_3) {
		updateFunc = [this](int range) {
				Move(2, range);
			};
	}
	else
	{
		updateFunc = nullptr;
	}


	sprite = std::make_shared<AnimatedSprite>();
	sprite->SetPos(pos);
	sprite->SetScale(1.3f);
	sprite->SetAnimMap(ANIM_TYPE::IDLE, { handles[0] }, 2.0f);
	sprite->SetAnimMap(ANIM_TYPE::FALL, { handles[0], handles[1], handles[2], handles[3], handles[4] }, 2.5f);
	sprite->SetAnimMap(ANIM_TYPE::BREAK, { handles[5], handles[6], handles[7], handles[8], handles[9] }, 3.0f, false);

	sprite->SetAnim(ANIM_TYPE::FALL);
	animManager.Add(sprite);
}

TitleObject::~TitleObject()
{
}

void TitleObject::Update(float dt)
{
	switch (type)
	{
	case UITYPE::TITLE_3:
		if (canMove)
		{
			updateFunc(moveRange.y);
			sprite->SetPos(pos);
		}
		animManager->Update(dt);
		if (sprite->IsFinish())
		{
			if (onBreakEnd)
			{
				onBreakEnd();
				onBreakEnd = nullptr;
			}
		}
		break;
	case UITYPE::TITLE_6:
		animManager->Update(dt);
		break;
	default:
		break;
	}

}

void TitleObject::Draw() const
{
	animManager->Draw();
}

void TitleObject::Move(int speed,int range)
{
	pos.y = min(pos.y + speed, range);
	if (pos.y >= range)
	{
		sprite->SetAnim(ANIM_TYPE::BREAK);
		canMove = false;
	}
}
