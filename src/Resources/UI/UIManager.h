#pragma once
#include <vector>
#include <memory>
#include "UIElement.h"

/// <summary>
/// UIのレイヤー種別
/// </summary>
enum class UILAYER {
    // シーンUI専用レイヤー
    SCENE,
    // 共通UIレイヤー
    COMMON,
    // シーン遷移専用レイヤー
    TRANSITION,
    MAX
};

/// <summary>
/// UI管理用クラス
/// ResourceManagerでロードしたハンドラを参照して管理する
/// ※ ロードは行わない
/// </summary>
class UIManager {
public:
    UIManager();
    ~UIManager();

    /// <summary>
    /// 表示するUIをレイヤー毎に追加
    /// </summary>
    /// <param name="ui">追加するUIクラスポインタ</param>
    /// <param name="layer">追加する対象レイヤー</param>
    void Add(std::shared_ptr<UIElement> ui, UILAYER layer);

    /// <summary>
    /// シーン専用UIを全て削除する
    /// ※ 共通UIや画面遷移専用UIはシーン特有の物ではないため、削除しない
    /// </summary>
    void ClearSceneUI();

    /// <summary>
    /// UIの更新
    /// </summary>
    /// <param name="dt">フェードイン/アウト等をする際のカウント</param>
    void Update(float dt);

    /// <summary>
    /// 画面表示メソッド
    /// </summary>
    /// <param name=""></param>
    void Draw(void) const;

private:
    /// <summary>
    /// シーン専用のUI格納用
    /// </summary>
    std::vector<std::weak_ptr<UIElement>> sceneUI;

    /// <summary>
    /// 共通専用のUI格納用
    /// </summary>
    std::vector<std::weak_ptr<UIElement>> commonUI;

    /// <summary>
    /// シーン遷移専用のUI格納用
    /// </summary>
    std::vector<std::weak_ptr<UIElement>> transitionUI;

    /// <summary>
    /// 各専用レイヤーに属するUIList取得
    /// </summary>
    /// <param name="l">取得したいレイヤー種別</param>
    /// <returns>レイヤーに属するUI</returns>
    std::vector<std::weak_ptr<UIElement>>& GetUIListByLayer(UILAYER l);

    /// <summary>
    /// レイヤー単位での描画メソッド
    /// </summary>
    /// <param name="layer">描画したいレイヤー種別</param>
    void DrawLayer(const std::vector<std::weak_ptr<UIElement>>& layer) const;
};
