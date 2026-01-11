#pragma once
#include <type_traits>

enum class MODE
{
	TRANING,
	VSCOM,
	VS2P,
	MAX
};

static MODE begin(MODE)
{
	return MODE::TRANING;
}

static MODE end(MODE)
{
	return MODE::MAX;
}

static MODE operator++(MODE& m)
{
	return (m =
		MODE(std::underlying_type<MODE>::type(m) + 1));
}

static MODE operator*(MODE m)
{
	return m;
}