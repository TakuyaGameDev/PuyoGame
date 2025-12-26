#include <DxLib.h>
#include "Keyboard.h"

Keyboard::Keyboard(PLAYERS p): Input(INPUT_TYPE::KEYBOARD, p)
{
	// ボタンのアクションマップの設定
	SetCommandMap();
}

Keyboard::~Keyboard()
{
}

void Keyboard::Update(void)
{
	// ボタン押下情報の更新
	GetHitKeyStateAll(&keyData[0]);
	// 指定のボタンを押下しているかの判定
	for (auto com : COMMANDS())
	{
		int tmp = commandMap[static_cast<int>(pl)][static_cast<int>(com)];
		inputMap[tmp][static_cast<int>(TRIGGER::OLD)]
			= inputMap[tmp][static_cast<int>(TRIGGER::NOW)];
		inputMap[tmp][static_cast<int>(TRIGGER::NOW)]
			= keyData[tmp];
	}
}

const bool Keyboard::GetInputTrigger(const COMMANDS& com)
{
	int tmp = commandMap[static_cast<int>(pl)][static_cast<int>(com)];
	// 今現在押していて、1フレーム前は押していない場合にtrueとなる
	return inputMap[tmp][static_cast<int>(TRIGGER::NOW)] && !inputMap[tmp][static_cast<int>(TRIGGER::OLD)];
}

void Keyboard::SetCommandMap(void)
{
	// 1Pのボタンのアクションマップ設定
	commandMap[static_cast<int>(pl)] =
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
