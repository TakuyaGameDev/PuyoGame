#include <DxLib.h>
#include "Application.h"
#include "../Input/Keyboard.h"

void Application::Run(void)
{
	if (!SysInit())
	{
		return;
	}
	while (!CheckHitKey(KEY_INPUT_ESCAPE))
	{
		inputs[static_cast<int>(PLAYERS::P_1)]->Update();
	}
}

void Application::Terminate(void)
{
	DxLib_End();
}

bool Application::SysInit()
{
	SetScreenSize(Vector2(1000, 600));
	SetMainWindowText(TITLE);
	SetGraphMode(this->screenSize.x, this->screenSize.y, 32);
	ChangeWindowMode(true);
	if (DxLib_Init() == 1)
	{
		return false;
	}

	inputs[static_cast<int>(PLAYERS::P_1)] = std::make_shared<Keyboard>();
	return true;
}
