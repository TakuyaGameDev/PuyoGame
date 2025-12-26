#pragma once
#include <string>
#include "Scene.h"

class SceneManager;
class Input;

/// <summary>
/// キャラクターセレクト画面クラス
/// </summary>
class CharacterSelectScene : public Scene
{
public:
	CharacterSelectScene(std::shared_ptr<SceneManager> m, std::shared_ptr<Input> i);
	~CharacterSelectScene();

	void Update(void);
private:
	std::weak_ptr<SceneManager> sceneManager;
	std::weak_ptr<Input> input;

	std::string tmp = "CharaSelectScene";

	void Draw(void);
};