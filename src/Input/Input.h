#pragma once
#include <array>
#include <map>

#include "Commands.h"

enum class TRIGGER
{
	NOW,
	OLD,
	MAX
};

enum class INPUT_TYPE
{
	KEYBOARD,
	GAMEPAD,
	MAX,
};

using TriggerMap = std::array<bool, static_cast<int>(TRIGGER::MAX)>;
using CommandMap = std::array<int, static_cast<int>(COMMANDS::MAX)>;
using InputMap = std::map<int, TriggerMap>;

class Input
{
public:
	Input(INPUT_TYPE type);
	~Input();
	virtual void Update(void) = 0;
	virtual const bool GetInputTrigger(const COMMANDS& com) = 0;
private:
	virtual void SetInputMap(void) = 0;
protected:
	INPUT_TYPE type;
	CommandMap commandMap;
	InputMap inputMap;
};