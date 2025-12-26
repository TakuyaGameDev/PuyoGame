#pragma once
#include <string>
#include "Scene.h"

class SceneManager;
class Input;

/// <summary>
/// ポーズ画面クラス
/// </summary>
class PauseScene : public Scene
{
public:
	PauseScene(std::shared_ptr<SceneManager> m, std::shared_ptr<Input> i);
	~PauseScene();

	void Update(void);
private:
	std::weak_ptr<SceneManager> sceneManager;
	std::weak_ptr<Input> input;

	std::string tmp = "PauseScene";

	void Draw(void);
};