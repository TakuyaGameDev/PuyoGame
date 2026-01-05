#include <DxLib.h>
#include "Cursor.h"

Cursor::Cursor(AnimationManager& animManager, std::weak_ptr<Input> input, const UITYPE& type, const Vector2& pos, const int& handle, MOVABLE_DIRECTION mDir) : handle(handle), movableDir(mDir), UIElement(type, pos, &animManager)
{
	speed = { 0,50 };
	this->input = input;
}

Cursor::~Cursor()
{
}

void Cursor::Update(float dt)
{
	Move();
}

void Cursor::Draw(void) const
{
	DrawGraph(pos.x, pos.y, handle, true);
}

void Cursor::Move(void)
{
	if (movableDir == MOVABLE_DIRECTION::VERTICAL)
	{
		if (input.lock()->GetInputTrigger(COMMANDS::UP))
		{
			pos.y -= speed.y;
		}
		if (input.lock()->GetInputTrigger(COMMANDS::DOWN))
		{
			pos.y += speed.y;
		}
	}
	if (movableDir == MOVABLE_DIRECTION::HOLIZON)
	{
		if (input.lock()->GetInputTrigger(COMMANDS::LEFT))
		{
			pos.x -= speed.x;
		}
		if (input.lock()->GetInputTrigger(COMMANDS::RIGHT))
		{
			pos.x += speed.x;
		}
	}

}
