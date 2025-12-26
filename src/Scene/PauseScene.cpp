#include <DxLib.h>
#include "../Input/Input.h"
#include "CharacterSelectScene.h"
#include "PauseScene.h"

PauseScene::PauseScene(std::shared_ptr<SceneManager> m, std::shared_ptr<Input> i) : sceneManager(m), input(i)
{
}

PauseScene::~PauseScene()
{
}

void PauseScene::Update(void)
{
	// 入力情報
	// ※ 入力情報は参照限定(weak_ptr)の為、必ずlockをしてから参照する
	if (auto i = input.lock())
	{
		// キャンセルボタン押下時
		if (i->GetInputTrigger(COMMANDS::CANCEL))
		{
			// 元の画面に返る(ポーズ画面を破棄する)
			// ※ 入力情報は参照限定(weak_ptr)の為、必ずlockをしてから参照する
			if (auto m = sceneManager.lock())
			{
				m->PopScene();
			}
		}
	}
	// 描画処理
	Draw();
}

void PauseScene::Draw(void)
{
	ClsDrawScreen();
	DrawFormatString(0, 0, 0xffffff, "%s", tmp.c_str());

	ScreenFlip();
}