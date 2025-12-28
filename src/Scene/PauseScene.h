#pragma once
#include <string>
#include "Scene.h"

class SceneManager;

/// <summary>
/// ポーズ画面クラス
/// </summary>
class PauseScene : public Scene
{
public:
	PauseScene(std::shared_ptr<SceneManager> m, InputSet iSet);
	~PauseScene();

	void Update(UIManager& uiManager);
	void OnEnter(UIManager& uiManager);
	void OnExit();
private:
	std::weak_ptr<SceneManager> sceneManager;

	std::string tmp = "PauseScene";

	void Draw(UIManager& uiManager);
};