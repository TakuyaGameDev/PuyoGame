#include <DxLib.h>
#include "Application.h"

void Application::Run(void)
{
	if (!SysInit())
	{
		return;
	}
	while (!CheckHitKey(KEY_INPUT_ESCAPE))
	{

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

	return true;
}
