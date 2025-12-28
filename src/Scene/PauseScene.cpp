#include <DxLib.h>
#include "../Input/Input.h"
#include "CharacterSelectScene.h"
#include "PauseScene.h"

PauseScene::PauseScene(std::shared_ptr<SceneManager> m, InputSet iSet) : sceneManager(m)
{
	inputSet = iSet;
}

PauseScene::~PauseScene()
{
}

void PauseScene::Update(UIManager& uiManager)
{
	// 入力情報
	// ※ 入力情報は参照限定(weak_ptr)の為、必ずlockをしてから参照する
	if (auto i = inputSet.p1.lock())
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
	uiManager.Update(1.0f);
}

void PauseScene::OnEnter(UIManager& uiManager) 
{

}

void PauseScene::OnExit() 
{

}

void PauseScene::Draw(UIManager& uiManager)
{
	DrawFormatString(0, 0, 0xffffff, "%s", tmp.c_str());
	uiManager.Draw();
}