#pragma once
#include <memory>
#include <array>
#include "Vector2.h"
#include "Players.h"

// 画面サイズ(横)
#define SCREEN_X 1000
// 画面サイズ(縦)
#define SCREEN_Y 600
// ウィンドウのタイトル
#define TITLE "PuyoGame"

class Input;
class SceneManager;

// 入力デバイス情報(プレイヤー配列として宣言)
using SharedInputs = std::array<std::shared_ptr<Input>, static_cast<int>(PLAYERS::MAX)>;
using SharedSceneManager = std::shared_ptr<SceneManager>;

/// <summary>
/// アプリケーションのエントリクラス
/// singleton
/// </summary>
class Application
{
public:
	/// <summary>
	/// シングルトンインスタンスを返す
	/// </summary>
	/// <returns>シングルトンインスタンス</returns>
	static Application& GetInstance(void)
	{
		static Application sInstance_;
		return sInstance_;
	}

	/// <summary>
	/// ゲームループ
	/// </summary>
	/// <param name=""></param>
	void Run(void);

	/// <summary>
	/// ゲームの終了
	/// </summary>
	/// <param name=""></param>
	void Terminate(void);

	/// <summary>
	/// ゲーム画面サイズの取得
	/// </summary>
	/// <param name=""></param>
	/// <returns>ゲーム画面サイズ</returns>
	const Vector2 GetScreenSize(void) const 
	{
		return this->screenSize;
	}

private:
	/// <summary>
	/// デフォルトコンストラクタの設定
	/// </summary>
	Application() = default;
	
	
	/// <summary>
	/// コピー禁止
	/// </summary>
	Application(const Application&) = delete;
	void operator=(const Application&) = delete;

	/// <summary>
	/// DxLibの初期化やゲームシステムの初期化
	/// </summary>
	/// <param name=""></param>
	/// <returns>初期化成功:true 失敗:false</returns>
	bool SysInit(void);

	/// <summary>
	/// ゲーム画面サイズ(x,y)
	/// </summary>
	Vector2 screenSize;

	/// <summary>
	/// ゲーム画面サイズの設定
	/// </summary>
	/// <param name="size">画面横、縦サイズ</param>
	void SetScreenSize(const Vector2& size)
	{
		this->screenSize.x = size.x;
		this->screenSize.y = size.y;
	}

	/// <summary>
	/// 入力デバイス(プレイヤー配列)
	/// </summary>
	SharedInputs inputs;

	/// <summary>
	/// シーン管理変数
	/// </summary>
	SharedSceneManager sceneManager;
};