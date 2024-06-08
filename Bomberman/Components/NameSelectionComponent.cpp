#include "NameSelectionComponent.h"

#include <glm/vec2.hpp>

#include "CharacterScrollComponent.h"
#include "../HighScoreListComponent.h"
#include "../PersistentData.h"
#include "Engine/DeltaTime.h"
#include "Engine/DesignPatterns/Singleton.h"
#include "SceneObjects/GameObject.h"

dae::NameSelectionComponent::NameSelectionComponent(dae::GameObject* pParent) : BaseComponent(pParent)
{
}


void dae::NameSelectionComponent::RegisterCharacter(CharacterScrollComponent* pCharacter)
{
	m_Character.push_back(pCharacter);
}

void dae::NameSelectionComponent::RegisterIndicators(GameObject* pIndicatorUp, GameObject* pIndicatorDown)
{
	m_pUpIndicator = pIndicatorUp;
	m_pDownIndicator = pIndicatorDown;
}

void dae::NameSelectionComponent::MoveIndicatorLeft()
{
	if(m_InputOnCooldown)
		return;
	--m_CurrentlySelectedCharacter;
	if(m_CurrentlySelectedCharacter < 0)
		m_CurrentlySelectedCharacter = static_cast<int>(m_Character.size() - 1);
	UpdateIndicatorPosition();
	m_InputOnCooldown = true;
}

void dae::NameSelectionComponent::MoveIndicatorRight()
{
	if(m_InputOnCooldown)
		return;
	++m_CurrentlySelectedCharacter;
	if(m_CurrentlySelectedCharacter >= static_cast<int>(m_Character.size()))
		m_CurrentlySelectedCharacter = 0;
	UpdateIndicatorPosition();
	m_InputOnCooldown = true;
}

void dae::NameSelectionComponent::ScrollCurrentCharacterUp()
{
	if(m_InputOnCooldown)
		return;
	m_Character[m_CurrentlySelectedCharacter]->IncrementCharacter();
	m_InputOnCooldown = true;
}

void dae::NameSelectionComponent::ScrollCurrentCharacterDown()
{
	if(m_InputOnCooldown)
		return;
	m_Character[m_CurrentlySelectedCharacter]->DecrementCharacter();
	m_InputOnCooldown = true;
}

void dae::NameSelectionComponent::SetHighscoreListComp(HighScoreListComponent* pHighscoreList)
{
	m_pHighScoreList = pHighscoreList;
}

void dae::NameSelectionComponent::Update()
{
	if(!m_InputOnCooldown)
		return;
	m_CurrentCooldown += Singleton<DeltaTime>::GetInstance().GetDeltaTime();
	if(m_CurrentCooldown > m_InputCooldown)
	{
		m_CurrentCooldown = 0;
		m_InputOnCooldown = false;
	}

}

void dae::NameSelectionComponent::SaveHighScore() 
{
	if(m_IsSaved)
		return;
	std::string name{};
	for(const auto& character : m_Character)
	{
		name += std::string{character->GetCurrentCharacter()};
	}
	m_pHighScoreList->AddScore(HighscoreEntry{PersistentData::GetInstance().GetScore(), name});
	m_IsSaved = true;
}

void dae::NameSelectionComponent::UpdateIndicatorPosition() const
{
	const float upOffSet{-15};
	const float downOffSet{30};
	const float leftOffSet{5};
	glm::vec2   currentCharacterPos{m_Character[m_CurrentlySelectedCharacter]->GetPosition()};
	m_pDownIndicator->SetPosition(currentCharacterPos.x + leftOffSet, currentCharacterPos.y + downOffSet);
	m_pUpIndicator->SetPosition(currentCharacterPos.x + leftOffSet, currentCharacterPos.y + upOffSet);

}
