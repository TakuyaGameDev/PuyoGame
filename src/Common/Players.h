#pragma once
#pragma once

#include <type_traits>

/// <summary>
/// プレイヤー定義クラス(enum)
/// </summary>
enum class PLAYERS
{
	P_1,
	P_2,
	MAX
};

static PLAYERS begin(PLAYERS)
{
	return PLAYERS::P_1;
}

static PLAYERS end(PLAYERS)
{
	return PLAYERS::MAX;
}

static PLAYERS operator++(PLAYERS& p)
{
	return (p =
		PLAYERS(std::underlying_type<PLAYERS>::type(p) + 1));
}

static PLAYERS operator*(PLAYERS p)
{
	return p;
}