#pragma once
#include <memory>
#include <array>
#include "../Input/InputSet.h"
#include "../Common/Players.h"
#include "SceneManager.h"
#include "../Resources/UI/UIManager.h"
#include "../Animation/AnimationManager.h"

/// <summary>
/// 画面フェードの状態enumの定義
/// </summary>
enum class FADE_STATE
{
	FADE_OUT,
	FADE_IN,
	NONE,
};

/// <summary>
/// 各シーンの親クラス
/// </summary>
class Scene
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Scene();
	virtual ~Scene() = default;

	/// <summary>
	/// シーンに入った時に1度だけ処理するメソッド(各継承先で処理を記述)
	/// </summary>
	/// <param name="uiManager">UI管理クラスの参照</param>
	virtual void OnEnter(UIManager& uiManager) = 0;

	/// <summary>
	/// シーンを去る時に1度だけ処理するメソッド(各継承先で処理を記述)
	/// </summary>
	/// <param name=""></param>
	virtual void OnExit() = 0;

	/// <summary>
	/// 更新処理(各継承先で処理を記述)
	/// </summary>
	/// <param name=""></param>
	virtual void Update(UIManager& uiManager) = 0;

	/// <summary>
	/// 描画メソッド(各継承先で処理を記述)
	/// </summary>
	/// <param name="uiManager">描画するUI</param>
	virtual void Draw(UIManager& uiManager) = 0;
private:

protected:
	AnimationManager animManager;
	InputSet inputSet;
};