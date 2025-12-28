#pragma once

#include <unordered_map>
#include <string>
#include "../Common/Vector2.h"
#include "../Common/ObjectType.h"

struct FontKey {
    std::string id;
    int size;

    bool operator==(const FontKey& o) const {
        return id == o.id && size == o.size;
    }
};

struct FontKeyHash {
    size_t operator()(const FontKey& k) const {
        return std::hash<std::string>()(k.id) ^ std::hash<int>()(k.size);
    }
};

/// <summary>
/// リソース管理用クラス(リソースハンドラの管理を担う)
/// </summary>
class ResourceManager {
public:
    /// <summary>
    /// シングルトンインスタンスを返す
    /// </summary>
    /// <returns>シングルトンインスタンス</returns>
    static ResourceManager& GetInstance() {
        static ResourceManager sInstance;
        return sInstance;
    }

    /// <summary>
    /// テクスチャのロード(単体)：オーバーロード
    /// </summary>
    /// <param name="id">ハンドラに割り当てるID文字列</param>
    /// <param name="path">ロード対象のリソースパス</param>
    void LoadTexture(const std::string& id, const std::string& path);

    /// <summary>
    /// ロード済みテクスチャの取得メソッド(単体)：オーバーロード
    /// </summary>
    /// <param name="id">ロード時にハンドラに割り当てられたID文字列</param>
    /// <returns>リソースハンドラ</returns>
    int GetTexture(const std::string& id);

    /// <summary>
    /// テクスチャのロード(複数)：オーバーロード
    /// </summary>
    /// <param name="id">ハンドラに割り当てるID文字列</param>
    /// <param name="path">ロード対象のリソースパス</param>
    /// <param name="xnum">ロードする画像のコマ数(横)</param>
    /// <param name="ynum">ロードする画像のコマ数(縦)</param>
    /// <param name="xsize">ロードする画像のサイズ(横)</param>
    /// <param name="ysize">ロードする画像のサイズ(縦)</param>
    void LoadTexture(const std::string& id, const std::string& path, const Vector2& num, const Vector2& size);

    /// <summary>
    /// オブジェクト種別によってsprite1枚分の画像ハンドラから特定の画像ハンドラグループを取得
    /// </summary>
    /// <param name="id">ロード時にハンドラに割り当てられたID文字列</param>
    /// <param name="objType">取得する画像ハンドラグループのオブジェクト種別</param>
    /// <returns>画像ハンドラグループ</returns>
    const std::vector<int> GetTextureGroup(const std::string& id, const OBJECT_TYPE& objType);

    /// <summary>
    /// テクスチャのリソースハンドラ取得(複数)：オーバーロード
    /// </summary>
    /// <param name="id">ロード時にハンドラに割り当てられたID文字列</param>
    /// <param name="index">取得する画像が何枚目にあたるかのindex番号</param>
    /// <returns></returns>
    int GetTexture(const std::string& id, int index);

    /// <summary>
    /// フォントのロード
    /// </summary>
    /// <param name="id">ハンドラに割り当てるID文字列</param>
    /// <param name="path">ロード対象のリソースパス</param>
    /// <param name="size">フォントのサイズ</param>
    /// <param name="loadOption">読み込む際のオプション</param>
    void LoadFont(const std::string& id, const std::string& path, int size, int loadOption = DX_FONTTYPE_ANTIALIASING);

    /// <summary>
    /// フォントのリソースハンドラの取得
    /// </summary>
    /// <param name="id"></param>
    /// <param name="size"></param>
    /// <returns></returns>
    int GetFont(const std::string& id, int size);

    /// <summary>
    /// リソースの全開放
    /// </summary>
    void ReleaseAll();
private:
    /// <summary>
    /// ロード時のリソースハンドラ配列(テクスチャ単体)
    /// </summary>
    std::unordered_map<std::string, int> textures;

    /// <summary>
    /// ロード時のリソースハンドラ配列(テクスチャ複数)
    /// </summary>
    std::unordered_map<std::string, std::vector<int>> divTextures;

    /// <summary>
    /// ロード時のリソースハンドラ配列(フォント)
    /// </summary>
    std::unordered_map<FontKey, int, FontKeyHash> fonts;
};