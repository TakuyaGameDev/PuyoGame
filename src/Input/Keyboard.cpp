#include <DxLib.h>
#include "Keyboard.h"

Keyboard::Keyboard(): Input(INPUT_TYPE::KEYBOARD)
{
	SetInputMap();
}

Keyboard::~Keyboard()
{
}

void Keyboard::Update(void)
{
	GetHitKeyStateAll(&keyData[0]);
	for (auto com : COMMANDS())
	{
		int tmp = commandMap[static_cast<int>(com)];
		inputMap[tmp][static_cast<int>(TRIGGER::OLD)]
			= inputMap[tmp][static_cast<int>(TRIGGER::NOW)];
		inputMap[tmp][static_cast<int>(TRIGGER::NOW)]
			= keyData[tmp];
	}
}

const bool Keyboard::GetInputTrigger(const COMMANDS& com)
{
	int tmp = commandMap[static_cast<int>(com)];
	return inputMap[tmp][static_cast<int>(TRIGGER::NOW)] && !inputMap[tmp][static_cast<int>(TRIGGER::OLD)];
}

void Keyboard::SetInputMap(void)
{
	commandMap =
		{
			KEY_INPUT_A,
			KEY_INPUT_D,
			KEY_INPUT_W,
			KEY_INPUT_S,
			KEY_INPUT_RETURN,
			KEY_INPUT_BACK,
			KEY_INPUT_P
		};
}
