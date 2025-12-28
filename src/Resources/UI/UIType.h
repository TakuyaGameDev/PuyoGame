#pragma once
#include <type_traits>

/// <summary>
/// UI‚Ìƒ^ƒCƒv
/// </summary>
enum class UITYPE {
    TITLE_1,
	TITLE_2,
	TITLE_3,
	TITLE_4,
	TITLE_5,
	TITLE_6,
	TITLE_7,
	TITLE_8,
	TITLE_9,
    MAX
};

static UITYPE begin(UITYPE)
{
	return UITYPE::TITLE_1;
}

static UITYPE end(UITYPE)
{
	return UITYPE::MAX;
}

static UITYPE operator++(UITYPE& type)
{
	return (type =
		UITYPE(std::underlying_type<UITYPE>::type(type) + 1));
}

static UITYPE operator*(UITYPE type)
{
	return type;
}