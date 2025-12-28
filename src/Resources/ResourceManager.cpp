#include <DxLib.h>
#include <iostream>
#include <filesystem>
#include "ResourceManager.h"

void ResourceManager::LoadTexture(const std::string& id, const std::string& path)
{
	textures[id] = LoadGraph(path.c_str());
}

void ResourceManager::LoadTexture(const std::string& id, const std::string& path, const Vector2& num, const Vector2& size)
{
	int total = num.x * num.y;
	std::vector<int> handles(total);
	LoadDivGraph(path.c_str(), total, num.x, num.y, size.x, size.y, handles.data());
	divTextures[id] = handles;
}

const std::vector<int> ResourceManager::GetTextureGroup(const std::string& id, const OBJECT_TYPE& objType)
{
	int base = 0;

	switch (objType) {
	case OBJECT_TYPE::LOOT_1:
		base = 0;
		break;
	case OBJECT_TYPE::LOOT_2:
		base = 10;
		break;
	case OBJECT_TYPE::LOOT_3:
		base = 20;
		break;
	case OBJECT_TYPE::LOOT_4:
		base = 30;
		break;
	default:
		break;
	}
	std::vector<int> frames;
	for (int i = 0; i < 10; ++i)
	{
		frames.push_back(GetTexture(id, base + i));
	}
	return frames;
}

int ResourceManager::GetTexture(const std::string& id, int index)
{
	return divTextures.at(id).at(index);
}

void ResourceManager::LoadFont(const std::string& id, const std::string& fontName, int size, int loadOption)
{
	fonts[{id, size}] = CreateFontToHandle(fontName.c_str(), size, 1, loadOption);
}

int ResourceManager::GetFont(const std::string& id, int size)
{
	return fonts.at({ id, size });
}

void ResourceManager::ReleaseAll()
{
	// テクスチャデータ(単体)の削除
	for (auto& pair : textures) {
		DeleteGraph(pair.second);
	}
	// テクスチャデータ(複数)の削除
	for (auto& pair : divTextures) {
		for (int h : pair.second) {
			DeleteGraph(h);
		}
	}
	// フォントデータの削除
	for (auto& pair : fonts) {
		DeleteFontToHandle(pair.second);
	}
}

int ResourceManager::GetTexture(const std::string& id)
{
	return textures.at(id);
}
