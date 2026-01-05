#include <DxLib.h>
#include "../Input/Input.h"
#include "TitleScene.h"
#include "CharacterSelectScene.h"
#include "../Resources/ResourceManager.h"
#include "../Resources/UI/Elements/Title/TitleText.h"
#include "../Resources/UI/Elements/Title/TitleObject.h"
#include "../Resources/UI/Elements/Common/Cursor.h"
#include "../Common/Application.h"

TitleScene::TitleScene(std::shared_ptr<SceneManager> m, InputSet iSet, bool isTrueTitle) : sceneManager(m), isTrueTitle(isTrueTitle)
{
	isDrawNextScene = false;
	if (isTrueTitle) 
	{
		fadeState = FADE_STATE::FADE_IN;
		fadeAlpha = 255.0f;
		fadeSpeed = 5.0f;
	}
	else
	{
		fadeState = FADE_STATE::NONE;
		fadeAlpha = 0.0f;
		fadeSpeed = 5.0f;
	}

	// 放射状フェード用
	fadeRadius = 0.0f;
	fadeRadiusSpeed = 20.0f;
	// 入力情報の設定(1Pと2P)
	inputSet = iSet;
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update(UIManager& uiManager)
{
	if (isTrueTitle)
	{
		if (fadeState == FADE_STATE::FADE_IN)
		{
			fadeAlpha -= fadeSpeed;
			if (fadeAlpha <= 0)
			{
				fadeAlpha = 0;
				fadeState = FADE_STATE::NONE;
				isDrawNextScene = false;
			}
		}
		// 入力情報
		// ※ 入力情報は参照限定(weak_ptr)の為、必ずlockをしてから参照する
		if (auto i = inputSet.p1.lock())
		{
			// 決定ボタン押下時
			if (i->GetInputTrigger(COMMANDS::DECISION))
			{
				// キャラクターセレクト画面へ遷移
				// ※ 入力情報は参照限定(weak_ptr)の為、必ずlockをしてから参照する
				if (auto m = sceneManager.lock())
				{
					m->ChangeScene(std::make_shared<CharacterSelectScene>(m, inputSet));
				}
			}
		}
	}
	else 
	{
		if (fadeState == FADE_STATE::FADE_OUT)
		{
			fadeRadius += fadeRadiusSpeed;
			fadeAlpha += fadeSpeed;

			if (fadeAlpha >= 255)
			{
				fadeAlpha = 255;

				// 新しいタイトルシーンに切り替え
				if (auto m = sceneManager.lock())
				{
					m->ChangeScene(std::make_shared<TitleScene>(m, inputSet, true));
				}

				fadeState = FADE_STATE::FADE_IN;
				fadeRadius = 0.0f; // フェードイン時はリセット
			}
		}
		else if (fadeState == FADE_STATE::FADE_IN)
		{
			fadeAlpha -= fadeSpeed;
			if (fadeAlpha <= 0)
			{
				fadeAlpha = 0;
				fadeState = FADE_STATE::NONE;
				isDrawNextScene = false;
			}
		}
	}
	uiManager.Update(1.0f);
}

void TitleScene::OnEnter(UIManager& uiManager)
{
	auto scrSize = Application::GetInstance().GetScreenSize();
	auto font_1 = ResourceManager::GetInstance().GetFont("title_1", 64);
	if (!isTrueTitle)
	{
		auto obj_1 = ResourceManager::GetInstance().GetTextureGroup("objects", OBJECT_TYPE::LOOT_1);

		auto titleUI_1 = std::make_shared<TitleText>(UITYPE::TITLE_1, font_1, Vector2(200, -64), GetColor(255, 0, 255), "Smashy");
		auto titleUI_2 = std::make_shared<TitleText>(UITYPE::TITLE_2, font_1, Vector2(scrSize.x - 400, scrSize.y), GetColor(255, 0, 255), "Loot");
		auto titleUI_3 = std::make_shared<TitleObject>(animManager, UITYPE::TITLE_3, obj_1, Vector2(scrSize.x - 480, -32));

		// コールバック関数の設定(titleUI_1に対して)
		titleUI_1->SetOnReachPosition([titleUI_3]() { titleUI_3->SetCanMove(true); });

		// コールバック関数の設定(titleUI_3に対して)
		titleUI_3->SetOnBreakEnd([this]()
			{
				isDrawNextScene = true;
				fadeState = FADE_STATE::FADE_OUT;
				fadeRadius = 0.0f;
			});

		uiManager.Add(titleUI_1, UILAYER::SCENE);
		uiManager.Add(titleUI_2, UILAYER::SCENE);
		uiManager.Add(titleUI_3, UILAYER::SCENE);

		uiList.push_back(titleUI_1);
		uiList.push_back(titleUI_2);
		uiList.push_back(titleUI_3);
	}
	else
	{
		auto font_2 = ResourceManager::GetInstance().GetFont("title_2", 32);
		auto cursor = ResourceManager::GetInstance().GetTexture("cursor");
		auto titleUI_4 = std::make_shared<TitleText>(UITYPE::TITLE_4, font_1, Vector2(200, 100), GetColor(255, 0, 255), "Smashy");
		auto titleUI_5 = std::make_shared<TitleText>(UITYPE::TITLE_5, font_1, Vector2(scrSize.x - 400, 100), GetColor(255, 0, 255), "Loot");
		auto titleUI_6 = std::make_shared<TitleText>(UITYPE::TITLE_6, font_1, Vector2(scrSize.x - 500, 100), GetColor(255, 0, 255), "x");
		auto titleUI_7 = std::make_shared<TitleText>(UITYPE::TITLE_7, font_2, Vector2(400, scrSize.y - 300), GetColor(255, 255, 255), "T R A N I N G");
		auto titleUI_8 = std::make_shared<TitleText>(UITYPE::TITLE_8, font_2, Vector2(400, scrSize.y - 250), GetColor(255, 255, 255), "S T A R T (vs COM)");
		auto titleUI_9 = std::make_shared<TitleText>(UITYPE::TITLE_9, font_2, Vector2(400, scrSize.y - 200), GetColor(255, 255, 255), "S T A R T (vs 2P)");
		auto titleUI_10 = std::make_shared<Cursor>(animManager, inputSet.p1, UITYPE::TITLE_10, Vector2(200, scrSize.y - 300), cursor, MOVABLE_DIRECTION::VERTICAL);

		uiManager.Add(titleUI_4, UILAYER::SCENE);
		uiManager.Add(titleUI_5, UILAYER::SCENE);
		uiManager.Add(titleUI_6, UILAYER::SCENE);
		uiManager.Add(titleUI_7, UILAYER::SCENE);
		uiManager.Add(titleUI_8, UILAYER::SCENE);
		uiManager.Add(titleUI_9, UILAYER::SCENE);
		uiManager.Add(titleUI_10, UILAYER::SCENE);

		uiList.push_back(titleUI_4);
		uiList.push_back(titleUI_5);
		uiList.push_back(titleUI_6);
		uiList.push_back(titleUI_7);
		uiList.push_back(titleUI_8);
		uiList.push_back(titleUI_9);
		uiList.push_back(titleUI_10);
	}
}

void TitleScene::OnExit()
{
	uiList.clear();
}

void TitleScene::Draw(UIManager& uiManager)
{
	if (isTrueTitle)
	{
		DrawFormatString(0, 0, 0xffffff, "%s", tmp.c_str());
		// 全画面白フェードイン
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(fadeAlpha));
		DrawBox(0, 0, Application::GetInstance().GetScreenSize().x,
			Application::GetInstance().GetScreenSize().y,
			GetColor(255, 255, 255), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else
	{
		if (fadeState == FADE_STATE::FADE_OUT)
		{
			// 放射状フェード（画面中央から半径fadeRadiusで白円を描く）
			int cx = Application::GetInstance().GetScreenSize().x / 2;
			int cy = Application::GetInstance().GetScreenSize().y / 2;

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(fadeAlpha));
			DrawCircle(cx, cy, static_cast<int>(fadeRadius), GetColor(255, 255, 255), true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		else if (fadeState == FADE_STATE::FADE_IN)
		{
			// 全画面白フェードイン
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(fadeAlpha));
			DrawBox(0, 0, Application::GetInstance().GetScreenSize().x,
				Application::GetInstance().GetScreenSize().y,
				GetColor(255, 255, 255), true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
	uiManager.Draw();
}