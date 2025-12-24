#pragma once

#include <type_traits>

// ÎÞÀÝ‚ÌŽí—Þ
enum class COMMANDS
{
	RIGHT,
	LEFT,
	UP,
	DOWN,
	DECISION,
	CANCEL,
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