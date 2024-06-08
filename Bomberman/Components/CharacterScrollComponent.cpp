#include "CharacterScrollComponent.h"

#include "SceneObjects/GameObject.h"
#include "Components/TextComponent.h"

dae::CharacterScrollComponent::CharacterScrollComponent(GameObject* pParent) : BaseComponent(pParent)
{
	m_pTextComp = pParent->GetComponentByClass<TextComponent>();
}

void dae::CharacterScrollComponent::IncrementCharacter()
{
	++m_CurrentCharacter;
	if(m_CurrentCharacter >= static_cast<int>(m_Characters.size()))
		m_CurrentCharacter = 0;

	m_pTextComp->SetText(std::string{m_Characters[m_CurrentCharacter]});
}

void dae::CharacterScrollComponent::DecrementCharacter()
{
	--m_CurrentCharacter;
	if(m_CurrentCharacter < 0)
		m_CurrentCharacter = static_cast<int>(m_Characters.size() - 1);
	m_pTextComp->SetText(std::string{m_Characters[m_CurrentCharacter]});
}

glm::vec2 dae::CharacterScrollComponent::GetPosition() const
{
	return GetParent()->GetTransform().GetWorldPosition();
}

char dae::CharacterScrollComponent::GetCurrentCharacter() const
{
	return m_Characters[m_CurrentCharacter];
}
