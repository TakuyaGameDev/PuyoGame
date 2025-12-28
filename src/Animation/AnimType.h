#pragma once
#include <type_traits>

/// <summary>
/// アニメーションタイプ
/// </summary>
enum class ANIM_TYPE {
	IDLE,
	FALL,
	BREAK,
	MAX
};

static ANIM_TYPE begin(ANIM_TYPE)
{
	return ANIM_TYPE::IDLE;
}

static ANIM_TYPE end(ANIM_TYPE)
{
	return ANIM_TYPE::MAX;
}

static ANIM_TYPE operator++(ANIM_TYPE& type)
{
	return (type =
		ANIM_TYPE(std::underlying_type<ANIM_TYPE>::type(type) + 1));
}

static ANIM_TYPE operator*(ANIM_TYPE type)
{
	return type;
}