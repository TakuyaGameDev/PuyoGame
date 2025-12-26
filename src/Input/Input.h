#pragma once
#include <array>
#include <map>

#include "Commands.h"
#include "../Common/Players.h"

/// <summary>
/// トリガー変数(enum)
/// </summary>
enum class TRIGGER
{
	// 今押しているか
	NOW,
	// 1フレーム前に押しているか
	OLD,
	MAX
};

/// <summary>
/// 入力デバイスタイプ(enum)
/// </summary>
enum class INPUT_TYPE
{
	KEYBOARD,
	GAMEPAD,
	MAX,
};

using TriggerMap = std::array<bool, static_cast<int>(TRIGGER::MAX)>;
using CommandMap = std::array<std::array<int, static_cast<int>(COMMANDS::MAX)>, static_cast<int>(PLAYERS::MAX)>;
using InputMap = std::map<int, TriggerMap>;

/// <summary>
/// 入力情報クラス
/// </summary>
class Input
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="type">入力デバイスタイプ</param>
	/// <param name="p">利用するプレイヤー</param>
	Input(INPUT_TYPE type,PLAYERS p);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Input();

	/// <summary>
	/// 更新メソッド(各継承先で処理を記述)
	/// </summary>
	/// <param name=""></param>
	virtual void Update(void) = 0;

	/// <summary>
	/// 入力トリガーフラグ取得メソッド(各継承先で処理を記述)
	/// </summary>
	/// <param name="com">押しているボタン</param>
	/// <returns>今押している場合:true そのほか:false</returns>
	virtual const bool GetInputTrigger(const COMMANDS& com) = 0;
private:

protected:
	/// <summary>
	/// ボタンのアクションマップを設定(各継承先で処理を記述)
	/// </summary>
	/// <param name=""></param>
	virtual void SetCommandMap(void) = 0;

	/// <summary>
	/// 入力デバイスタイプ
	/// </summary>
	INPUT_TYPE type;

	/// <summary>
	/// ボタンのアクションマップ変数
	/// </summary>
	CommandMap commandMap;

	/// <summary>
	/// 入力情報変数
	/// </summary>
	InputMap inputMap;

	/// <summary>
	/// プレイヤー情報変数
	/// </summary>
	PLAYERS pl;
};