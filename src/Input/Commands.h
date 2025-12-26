#pragma once

#include <type_traits>

/// <summary>
/// アクションボタンのマッピングクラス(enum)
/// </summary>
enum class COMMANDS
{
	// 右
	RIGHT,
	// 左
	LEFT,
	// 上
	UP,
	// 下
	DOWN,
	// 決定
	DECISION,
	// キャンセル
	CANCEL,
	// ポーズ
	PAUSE,
	MAX
};

static COMMANDS begin(COMMANDS)
{
	return COMMANDS::RIGHT;
}

static COMMANDS end(COMMANDS)
{
	return COMMANDS::MAX;
}

static COMMANDS operator++(COMMANDS& com)
{
	return (com =
		COMMANDS(std::underlying_type<COMMANDS>::type(com) + 1));
}

static COMMANDS operator*(COMMANDS com)
{
	return com;
}