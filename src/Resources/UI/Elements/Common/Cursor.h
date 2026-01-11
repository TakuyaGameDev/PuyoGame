#pragma once
#include <functional>
#include "../../UIElement.h"
#include "../../../../Input/Input.h"

using PositionCallback = std::function<void(const Vector2& pos)>;

// 移動可能な方向
enum class MOVABLE_DIRECTION
{
	// 垂直方向
	VERTICAL,
	// 水平方向
	HOLIZON,
	// 垂直/水平両方
	BOTH,
	MAX
};

/// <summary>
/// カーソルクラス(種別：UI)
/// </summary>
class Cursor : public UIElement 
{
public:
	Cursor(AnimationManager& animManager, std::weak_ptr<Input> input, const UITYPE& type, const Vector2& pos,const Vector2& range, const int& handle, MOVABLE_DIRECTION mDir);
	~Cursor();

	void Update(float dt);
	void Draw(void) const;

	void SetMode(PositionCallback cb) { setMode = cb; }

private:

	void Move(void);
	void SlightMove(float dt);

	const MOVABLE_DIRECTION movableDir;
	const int handle;
	Vector2 speed;
	float time;
	Vector2 drawPos;

	Vector2 basePos;
	Vector2 moveRange;

	PositionCallback setMode = nullptr;

	std::weak_ptr<Input> input;
};
