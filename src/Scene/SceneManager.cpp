#include "SceneManager.h"
#include "Scene.h"

SceneManager::SceneManager(UIManager& uiManager):uiManager(uiManager)
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Update(float dt)
{
	if (!sceneStack.empty()) {
		sceneStack.top()->Update(uiManager);
	}
}

void SceneManager::Draw()
{
	if (!sceneStack.empty()) {
		sceneStack.top()->Draw(uiManager);
	}
}

void SceneManager::ChangeScene(ScenePtr newScene)
{
	// シーンスタック内の削除
	if (!sceneStack.empty()) {
		sceneStack.top()->OnExit();
		sceneStack.pop();
	}
	// 新しいシーンの追加
	sceneStack.push(newScene);
	sceneStack.top()->OnEnter(uiManager);
}
void SceneManager::PushScene(ScenePtr newScene)
{
	// 新しいシーンの追加
	sceneStack.push(newScene);
	sceneStack.top()->OnEnter(uiManager);
}

void SceneManager::PopScene(void) {
	// シーンスタック内の削除
	if (!sceneStack.empty()) {
		sceneStack.top()->OnExit();
		sceneStack.pop();
	}
	// 削除した後に新しいシーンが残っていればそのシーンの初期化
	// 例) ポーズ→ゲームプレイ画面に戻る場合等
	if (!sceneStack.empty()) {
		sceneStack.top()->OnEnter(uiManager);
	}
}

ScenePtr SceneManager::GetCurrentScene(void) {
	return sceneStack.empty() ? nullptr : sceneStack.top();
}

std::shared_ptr<SceneManager> SceneManager::GetShared() {
	return shared_from_this();
}
