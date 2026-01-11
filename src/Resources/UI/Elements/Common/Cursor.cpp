#include <DxLib.h>
#include <algorithm>
#include "Cursor.h"

Cursor::Cursor(AnimationManager& animManager, std::weak_ptr<Input> input, const UITYPE& type, const Vector2& pos, const Vector2& range, const int& handle, MOVABLE_DIRECTION mDir) : handle(handle), movableDir(mDir), UIElement(type, pos, &animManager)
{
	speed = { 0,50 };
	drawPos = pos;
	basePos = pos;
	moveRange = range;
	time = 0;
	this->input = input;
}

Cursor::~Cursor()
{
}

void Cursor::Update(float dt)
{
	Move();
	SlightMove(dt);
}

void Cursor::Draw(void) const
{
	DrawGraph(drawPos.x, drawPos.y, handle, true);
}

void Cursor::Move(void)
{
	if (movableDir == MOVABLE_DIRECTION::VERTICAL)
	{
		int newSpeedY = 0;
		if (input.lock()->GetInputTrigger(COMMANDS::UP))
		{
			if (pos.y - speed.y >= basePos.y) 
			{
				newSpeedY = -speed.y;
			}
		}
		if (input.lock()->GetInputTrigger(COMMANDS::DOWN))
		{
			if (pos.y + speed.y <= moveRange.y) 
			{
				newSpeedY = speed.y;
			}
		}
		pos.y += newSpeedY;
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
	if (setMode) 
	{
		setMode(pos);
	}
}

void Cursor::SlightMove(float dt)
{
	time += dt;
	
	float amplitude = 8.0f;   // óhÇÍïù(px)
	float speed = 0.1f;       // óhÇÍë¨ìx

	float offsetX = sin(time * speed) * amplitude;

	drawPos = { pos.x + offsetX, pos.y };
}
