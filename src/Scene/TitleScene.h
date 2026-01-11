#pragma once
#include <string>
#include "Scene.h"
#include "../Common/Mode.h"

class SceneManager;

/// <summary>
/// タイトル画面クラス
/// </summary>
class TitleScene: public Scene
{
public:
	TitleScene(std::shared_ptr<SceneManager> m, InputSet iSet, bool isTrueTitle = false);
	~TitleScene();

	void Update(UIManager& uiManager);
	void OnEnter(UIManager& uiManager);
	void OnExit();

private:
	/// <summary>
	/// タイトルに入る前のアニメーションシーンかどうかの判定
	/// true: タイトルシーン
	/// false: タイトルに入る前のアニメーションシーン
	/// </summary>
	bool isTrueTitle;
	std::weak_ptr<SceneManager> sceneManager;

	std::string tmp = "TitleScene";

	void Draw(UIManager& uiManager);
	bool isDrawNextScene;

	std::vector<std::shared_ptr<UIElement>> uiList;

	FADE_STATE fadeState;
	float fadeAlpha;
	float fadeSpeed;
	// 放射状フェード用
	float fadeRadius;
	float fadeRadiusSpeed;

	MODE mode;
};