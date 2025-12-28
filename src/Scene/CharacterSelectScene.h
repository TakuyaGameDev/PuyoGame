#pragma once
#include <string>
#include "Scene.h"

class SceneManager;

/// <summary>
/// キャラクターセレクト画面クラス
/// </summary>
class CharacterSelectScene : public Scene
{
public:
	CharacterSelectScene(std::shared_ptr<SceneManager> m, InputSet iSet);
	~CharacterSelectScene();

	void Update(UIManager& uiManager);
	void OnEnter(UIManager& uiManager);
	void OnExit();
private:
	std::weak_ptr<SceneManager> sceneManager;

	std::string tmp = "CharaSelectScene";

	void Draw(UIManager& uiManager);
};