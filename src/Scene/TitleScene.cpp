#include <DxLib.h>
#include "../Input/Input.h"
#include "TitleScene.h"
#include "CharacterSelectScene.h"

TitleScene::TitleScene(std::shared_ptr<SceneManager> m, std::shared_ptr<Input> i) : sceneManager(m), input(i)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update(void)
{
	// 入力情報
	// ※ 入力情報は参照限定(weak_ptr)の為、必ずlockをしてから参照する
	if (auto i = input.lock()) 
	{
		// 決定ボタン押下時
		if (i->GetInputTrigger(COMMANDS::DECISION))
		{
			// キャラクターセレクト画面へ遷移
			// ※ 入力情報は参照限定(weak_ptr)の為、必ずlockをしてから参照する
			if (auto m = sceneManager.lock())
			{
				m->ChangeScene(std::make_shared<CharacterSelectScene>(m, i));
			}
		}
	}
	// 描画処理
	Draw();
}

void TitleScene::Draw(void)
{
	ClsDrawScreen();
	DrawFormatString(0, 0, 0xffffff,"%s", tmp.c_str());

	ScreenFlip();
}