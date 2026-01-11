#pragma once
#include <string>
#include "Scene.h"
#include "../Common/Mode.h"

class SceneManager;

/// <summary>
/// キャラクターセレクト画面クラス
/// </summary>
class CharacterSelectScene : public Scene
{
public:
	CharacterSelectScene(std::shared_ptr<SceneManager> m, InputSet iSet, const MODE& mode);
	~CharacterSelectScene();

	void Update(UIManager& uiManager);
	void OnEnter(UIManager& uiManager);
	void OnExit();
private:
	std::weak_ptr<SceneManager> sceneManager;
	std::vector<std::shared_ptr<UIElement>> uiList;

	std::string tmp = "CharaSelectScene";

	void Draw(UIManager& uiManager);

	FADE_STATE fadeState;
	float fadeAlpha;
	float fadeSpeed;
	// 放射状フェード用
	float fadeRadius;
	float fadeRadiusSpeed;

	const MODE selectedMode;
};