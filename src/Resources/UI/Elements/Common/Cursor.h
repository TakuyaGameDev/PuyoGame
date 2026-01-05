#pragma once
#include "../../UIElement.h"
#include "../../../../Input/Input.h"

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
	Cursor(AnimationManager& animManager, std::weak_ptr<Input> input, const UITYPE& type, const Vector2& pos, const int& handle, MOVABLE_DIRECTION mDir);
	~Cursor();

	void Update(float dt);
	void Draw(void) const;

private:

	void Move(void);

	const MOVABLE_DIRECTION movableDir;
	const int handle;
	Vector2 speed;

	std::weak_ptr<Input> input;
};
