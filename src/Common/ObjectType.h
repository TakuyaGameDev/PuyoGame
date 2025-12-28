#pragma once
#include <type_traits>

/// <summary>
/// オブジェクト種別定義クラス(enum)
/// </summary>
enum class OBJECT_TYPE
{
	// 宝箱1
	LOOT_1,
	// 宝箱2
	LOOT_2,
	// 宝箱3
	LOOT_3,
	// 宝箱4
	LOOT_4,
	MAX
};

static OBJECT_TYPE begin(OBJECT_TYPE)
{
	return OBJECT_TYPE::LOOT_1;
}

static OBJECT_TYPE end(OBJECT_TYPE)
{
	return OBJECT_TYPE::MAX;
}

static OBJECT_TYPE operator++(OBJECT_TYPE& type)
{
	return (type =
		OBJECT_TYPE(std::underlying_type<OBJECT_TYPE>::type(type) + 1));
}

static OBJECT_TYPE operator*(OBJECT_TYPE type)
{
	return type;
}