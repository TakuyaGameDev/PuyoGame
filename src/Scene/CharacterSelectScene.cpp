#include <DxLib.h>
#include "../Input/Input.h"
#include "CharacterSelectScene.h"
#include "PauseScene.h"
#include "../Common/Application.h"

CharacterSelectScene::CharacterSelectScene(std::shared_ptr<SceneManager> m, InputSet iSet, const MODE& mode) : sceneManager(m), selectedMode(mode)
{
	inputSet = iSet;
	fadeState = FADE_STATE::FADE_IN;
	fadeAlpha = 255.0f;
	fadeSpeed = 5.0f;
}

CharacterSelectScene::~CharacterSelectScene()
{
}

void CharacterSelectScene::Update(UIManager& uiManager)
{
	if (fadeState == FADE_STATE::FADE_OUT)
	{
		fadeRadius += fadeRadiusSpeed;
		fadeAlpha += fadeSpeed;

		if (fadeAlpha >= 255)
		{
			fadeAlpha = 255;

			// 新しいタイトルシーンに切り替え
			//if (auto m = sceneManager.lock())
			//{
			//	m->ChangeScene(std::make_shared<TitleScene>(m, inputSet, true));
			//}

			fadeState = FADE_STATE::FADE_IN;
			fadeRadius = 0.0f; // フェードイン時はリセット
		}
	}
	else if (fadeState == FADE_STATE::FADE_IN)
	{
		fadeAlpha -= fadeSpeed;
		if (fadeAlpha <= 0)
		{
			fadeAlpha = 0;
			fadeState = FADE_STATE::NONE;
		}
	}
	// 入力情報
	// ※ 入力情報は参照限定(weak_ptr)の為、必ずlockをしてから参照する
	if (auto i = inputSet.p1.lock())
	{
		//// ポーズボタン押下時
		//if (i->GetInputTrigger(COMMANDS::PAUSE))
		//{
		//	// ポーズ画面へ遷移
		//	// ※ 入力情報は参照限定(weak_ptr)の為、必ずlockをしてから参照する
		//	if (auto m = sceneManager.lock())
		//	{
		//		m->PushScene(std::make_shared<PauseScene>(m, inputSet));
		//	}
		//}
	}
	uiManager.Update(1.0f);
}

void CharacterSelectScene::OnEnter(UIManager& uiManager) 
{

}

void CharacterSelectScene::OnExit() 
{
	uiList.clear();
}

void CharacterSelectScene::Draw(UIManager& uiManager)
{
	DrawFormatString(0, 0, 0xffffff, "%s", tmp.c_str());
	if (fadeState == FADE_STATE::FADE_OUT)
	{
		// 放射状フェード（画面中央から半径fadeRadiusで白円を描く）
		int cx = Application::GetInstance().GetScreenSize().x / 2;
		int cy = Application::GetInstance().GetScreenSize().y / 2;

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(fadeAlpha));
		DrawCircle(cx, cy, static_cast<int>(fadeRadius), GetColor(255, 255, 255), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else if (fadeState == FADE_STATE::FADE_IN)
	{
		// 全画面白フェードイン
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(fadeAlpha));
		DrawBox(0, 0, Application::GetInstance().GetScreenSize().x,
			Application::GetInstance().GetScreenSize().y,
			GetColor(255, 255, 255), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	uiManager.Draw();
}