#include <DxLib.h>
#include <string>
#include "Application.h"
#include "../Input/InputSet.h"
#include "../Input/Keyboard.h"
#include "../Scene/SceneManager.h"
#include "../Scene/TitleScene.h"
#include "../Resources/ResourceManager.h"

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
		float dt = 1.0f / 60.0f;
		// 入力デバイスの更新
		inputs[static_cast<int>(PLAYERS::P_1)]->Update();
		// シーンの更新
		sceneManager->Update(dt);

		// シーンの描画
		ClsDrawScreen();
		sceneManager->Draw();
		ScreenFlip();
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
	SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8);
	if (DxLib_Init() == 1)
	{
		return false;
	}
	// リソース群のロード
	LoadResources();
	// 入力デバイス(1P)のインスタンス
	inputs[static_cast<int>(PLAYERS::P_1)] = std::make_shared<Keyboard>(PLAYERS::P_1);
	// 入力デバイス(2P)のインスタンス
	inputs[static_cast<int>(PLAYERS::P_2)] = std::make_shared<Keyboard>(PLAYERS::P_2);

	InputSet inputSet;
	//inputSet構造体への格納
	inputSet.p1 = inputs[static_cast<int>(PLAYERS::P_1)];
	inputSet.p2 = inputs[static_cast<int>(PLAYERS::P_2)];

	// UI管理クラスのインスタンス
	uiManager = std::make_unique<UIManager>();
	// シーン管理クラスのインスタンス
	sceneManager = std::make_shared<SceneManager>(*uiManager);
	// 初期画面をタイトル画面に設定
	sceneManager->ChangeScene(std::make_shared<TitleScene>(sceneManager, inputSet));
	return true;
}

bool Application::LoadResources(void)
{
	auto& resourceManager = ResourceManager::GetInstance();
	resourceManager.LoadFont("title_1", "Eva Poshy", 64, DX_FONTTYPE_EDGE);
	resourceManager.LoadFont("title_2", "Eva Poshy", 32, DX_FONTTYPE_EDGE);

	resourceManager.LoadTexture("objects", "Resources/Objects/Chests.png", { 5, 8 }, { 48, 32 });
	return true;
}
