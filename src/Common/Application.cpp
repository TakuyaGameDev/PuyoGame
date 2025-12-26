#include <DxLib.h>
#include "Application.h"
#include "../Input/Keyboard.h"
#include "../Scene/SceneManager.h"
#include "../Scene/TitleScene.h"

void Application::Run(void)
{
	// システムの初期化
	if (!SysInit())
	{
		return;
	}
	// ゲームループ
	while (!CheckHitKey(KEY_INPUT_ESCAPE))
	{
		// 入力デバイスの更新
		inputs[static_cast<int>(PLAYERS::P_1)]->Update();
		// シーンの更新
		if (auto scene = sceneManager->GetCurrentScene()) {
			scene->Update();
		}
	}
}

void Application::Terminate(void)
{
	DxLib_End();
}

bool Application::SysInit()
{
	// 画面サイズの初期化
	SetScreenSize(Vector2(SCREEN_X, SCREEN_Y));
	// ウィンドウテキストの初期化
	SetMainWindowText(TITLE);
	// 描画モードの初期化
	SetGraphMode(this->screenSize.x, this->screenSize.y, 32);
	ChangeWindowMode(true);
	if (DxLib_Init() == 1)
	{
		return false;
	}
	// 入力デバイス(1P)のインスタンス
	inputs[static_cast<int>(PLAYERS::P_1)] = std::make_shared<Keyboard>(PLAYERS::P_1);
	// シーン管理クラスのインスタンス
	sceneManager = std::make_shared<SceneManager>();
	// 初期画面をタイトル画面に設定
	sceneManager->ChangeScene(std::make_shared<TitleScene>(sceneManager, inputs[static_cast<int>(PLAYERS::P_1)]));
	return true;
}
