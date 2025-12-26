#include <DxLib.h>
#include "../Input/Input.h"
#include "CharacterSelectScene.h"
#include "PauseScene.h"

CharacterSelectScene::CharacterSelectScene(std::shared_ptr<SceneManager> m, std::shared_ptr<Input> i) : sceneManager(m), input(i)
{
}

CharacterSelectScene::~CharacterSelectScene()
{
}

void CharacterSelectScene::Update(void)
{
	// 入力情報
	// ※ 入力情報は参照限定(weak_ptr)の為、必ずlockをしてから参照する
	if (auto i = input.lock())
	{
		// ポーズボタン押下時
		if (i->GetInputTrigger(COMMANDS::PAUSE))
		{
			// ポーズ画面へ遷移
			// ※ 入力情報は参照限定(weak_ptr)の為、必ずlockをしてから参照する
			if (auto m = sceneManager.lock())
			{
				m->PushScene(std::make_shared<PauseScene>(m, i));
			}
		}
	}
	// 描画処理
	Draw();
}

void CharacterSelectScene::Draw(void)
{
	ClsDrawScreen();
	DrawFormatString(0, 0, 0xffffff, "%s", tmp.c_str());

	ScreenFlip();
}