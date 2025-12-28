#pragma once
#include <memory>
#include "Input.h"

struct InputSet
{
	std::weak_ptr<Input> p1;
	std::weak_ptr<Input> p2;
};