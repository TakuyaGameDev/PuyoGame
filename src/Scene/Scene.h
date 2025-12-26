#pragma once
#include <memory>
#include <array>
#include "../Common/Players.h"
#include "SceneManager.h"

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
	/// シーンに入った時に1度だけ処理するメソッド
	/// </summary>
	/// <param name=""></param>
	virtual void OnEnter(void);

	/// <summary>
	/// シーンを去る時に1度だけ処理するメソッド
	/// </summary>
	/// <param name=""></param>
	virtual void OnExit(void);

	/// <summary>
	/// 更新処理(各継承先で処理を記述)
	/// </summary>
	/// <param name=""></param>
	virtual void Update(void) = 0;
private:

protected:
	/// <summary>
	/// 描画メソッド(各継承先で処理を記述)
	/// </summary>
	/// <param name=""></param>
	virtual void Draw(void) = 0;
};