#include <DxLib.h>
#include "src/Common/Application.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	auto& app = Application::GetInstance();

	app.Run();

	app.Terminate();
}