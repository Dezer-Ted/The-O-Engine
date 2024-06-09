#include "MenuNavigatorComponent.h"

#include "../SceneNavigator.h"
#include "../SceneUtils/LevelLoader.h"
#include "Engine/DeltaTime.h"
#include "Engine/DesignPatterns/Singleton.h"
#include "SceneObjects/GameObject.h"
#include "SceneObjects/SceneManager.h"

dae::MenuNavigatorComponent::MenuNavigatorComponent(dae::GameObject* pParent) : BaseComponent(pParent)
{
}

void dae::MenuNavigatorComponent::MoveUp()
{
	if(m_IsOnCooldown)
		return;
	--m_CurrentlySelectedItem;
	if(m_CurrentlySelectedItem < 0)
	{
		m_CurrentlySelectedItem = static_cast<int>(m_MenuObjects.size() - 1);
	}
	UpdateIndicatorPosition();
	m_IsOnCooldown = true;
}

void dae::MenuNavigatorComponent::MoveDown()
{
	if(m_IsOnCooldown)
		return;
	++m_CurrentlySelectedItem;
	if(m_CurrentlySelectedItem >= static_cast<int>(m_MenuObjects.size()))
	{
		m_CurrentlySelectedItem = 0;
	}
	UpdateIndicatorPosition();
	m_IsOnCooldown = true;
}

void dae::MenuNavigatorComponent::ExecuteCurrentlySelected() const
{
	switch(m_CurrentlySelectedItem)
	{
	case 0:
		LevelLoader::m_GameMode = GameMode::Single;
		break;
	case 1:
		//TODO start versus mode

		LevelLoader::m_GameMode = GameMode::Versus;
		break;
	case 2:
		//TODO start Coop mode

		LevelLoader::m_GameMode = GameMode::Coop;
		break;
	default:
		break;
	}
	SceneNavigator::UnloadStage();
}

void dae::MenuNavigatorComponent::RegisterMenuItem(GameObject* pMenuItem)
{
	m_MenuObjects.push_back(pMenuItem);
}

void dae::MenuNavigatorComponent::Update()
{
	if(!m_IsOnCooldown)
		return;
	m_CurrentCooldown += Singleton<DeltaTime>::GetInstance().GetDeltaTime();
	if(m_CurrentCooldown > m_SwitchCooldown)
	{
		m_IsOnCooldown = false;
		m_CurrentCooldown = 0.f;
	}
}

void dae::MenuNavigatorComponent::UpdateIndicatorPosition() const
{

	const glm::vec2 currentPos{GetParent()->GetTransform().GetWorldPosition()};
	const glm::vec2 desiredPos{m_MenuObjects[m_CurrentlySelectedItem]->GetTransform().GetWorldPosition()};
	GetParent()->SetPosition(currentPos.x, desiredPos.y);
}
