#pragma once
#include <memory>
#include <stack>

class Scene;
/// <summary>
/// 各シーンに対するポインタ
/// </summary>
using ScenePtr = std::shared_ptr<Scene>;

/// <summary>
/// シーン遷移管理クラス
/// std::enable_shared_from_this：自身を参照可能に
/// </summary>
class SceneManager : public std::enable_shared_from_this<SceneManager>
{
public:
	SceneManager();
	~SceneManager();
	/// <summary>
	/// シーンの変更(初期シーン設定時にも使用可能)
	/// </summary>
	/// <param name="newScene">新しいシーン</param>
	void ChangeScene(ScenePtr newScene);

	/// <summary>
	/// シーンスタックに新しいシーンを詰め込む
	/// </summary>
	/// <param name="newScene">新しいシーン</param>
	void PushScene(ScenePtr newScene);

	/// <summary>
	/// シーンスタックから取り除く
	/// </summary>
	void PopScene(void);

	/// <summary>
	/// 現在のシーンを取得
	/// </summary>
	/// <returns>現在のシーンのポインタ(shared_ptr)</returns>
	ScenePtr GetCurrentScene(void);

	/// <summary>
	/// 自身を取得
	/// </summary>
	/// <returns>自身のポインタ(shared_ptr)</returns>
	std::shared_ptr<SceneManager> GetShared(void);

private:
	/// <summary>
	/// シーンを格納していくスタック変数
	/// </summary>
	std::stack<ScenePtr> sceneStack;
};