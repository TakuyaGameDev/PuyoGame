#include <DxLib.h>
#include "../Input/Input.h"
#include "CharacterSelectScene.h"
#include "PauseScene.h"

CharacterSelectScene::CharacterSelectScene(std::shared_ptr<SceneManager> m, InputSet iSet) : sceneManager(m)
{
	inputSet = iSet;
}

CharacterSelectScene::~CharacterSelectScene()
{
}

void CharacterSelectScene::Update(UIManager& uiManager)
{
	// 入力情報
	// ※ 入力情報は参照限定(weak_ptr)の為、必ずlockをしてから参照する
	if (auto i = inputSet.p1.lock())
	{
		// ポーズボタン押下時
		if (i->GetInputTrigger(COMMANDS::PAUSE))
		{
			// ポーズ画面へ遷移
			// ※ 入力情報は参照限定(weak_ptr)の為、必ずlockをしてから参照する
			if (auto m = sceneManager.lock())
			{
				m->PushScene(std::make_shared<PauseScene>(m, inputSet));
			}
		}
	}
	uiManager.Update(1.0f);
}

void CharacterSelectScene::OnEnter(UIManager& uiManager) 
{

}

void CharacterSelectScene::OnExit() 
{

}

void CharacterSelectScene::Draw(UIManager& uiManager)
{
	DrawFormatString(0, 0, 0xffffff, "%s", tmp.c_str());
	uiManager.Draw();
}