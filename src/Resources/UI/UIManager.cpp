#include "UIManager.h"

UIManager::UIManager()
{
}

UIManager::~UIManager()
{
}

void UIManager::Add(std::shared_ptr<UIElement> ui, UILAYER layer)
{
	GetUIListByLayer(layer).push_back(ui);
}

void UIManager::ClearSceneUI(void)
{
	sceneUI.clear();
}

void UIManager::Update(float dt)
{
	for (auto* layer : { &sceneUI, &commonUI, &transitionUI }) 
	{
		for (auto it = layer->begin(); it != layer->end(); ) 
		{
			if (auto ui = it->lock()) {
				if (ui->visible) {
					ui->Update(dt);
				}
				++it;
			}
			else 
			{
				it = layer->erase(it); // îjä¸çœÇ›UIÇÕçÌèú
			}
		}
	}
}

void UIManager::Draw(void) const
{
	DrawLayer(sceneUI);
	DrawLayer(commonUI);
	DrawLayer(transitionUI);
}

std::vector<std::weak_ptr<UIElement>>& UIManager::GetUIListByLayer(UILAYER l)
{
	switch (l) {
		case UILAYER::SCENE: return sceneUI;
		case UILAYER::COMMON: return commonUI;
		case UILAYER::TRANSITION: return transitionUI;
	}
	return sceneUI;
}

void UIManager::DrawLayer(const std::vector<std::weak_ptr<UIElement>>& layer) const
{
	for (auto& wptr : layer) 
	{
		if (auto ui = wptr.lock()) 
		{
			if (ui->visible) ui->Draw();
		}
	}
}
