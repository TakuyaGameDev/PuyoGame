#pragma once
#include <string>
#include "Scene.h"

class SceneManager;
class Input;

/// <summary>
/// タイトル画面クラス
/// </summary>
class TitleScene: public Scene
{
public:
	TitleScene(std::shared_ptr<SceneManager> m, std::shared_ptr<Input> i);
	~TitleScene();

	void Update(void);
private:
	std::weak_ptr<SceneManager> sceneManager;
	std::weak_ptr<Input> input;

	std::string tmp = "TitleScene";

	void Draw(void);
};