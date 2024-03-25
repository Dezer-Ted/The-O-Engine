#include "LifeDisplayComponent.h"

#include "PlayerComponent.h"
#include "TextComponent.h"
#include "../ResourceManager.h"

dae::LifeDisplayComponent::LifeDisplayComponent(GameObject* pParent) : BaseComponent(pParent)
{
	m_pTextComp = pParent->AddComponent<TextComponent>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	m_pTextComp->SetText(m_BaseText, font, {255, 255, 255, 255});
}

void dae::LifeDisplayComponent::Notify(Utils::GameEvent event, BaseComponent* components)
{
	switch(event)
	{
	case Utils::PlayerSpawn:
	case Utils::GameEvent::PlayerDied:
		const PlayerComponent* lifeComp{dynamic_cast<PlayerComponent*>(components)};
		if(lifeComp)
			UpdateText(lifeComp);
		break;
	}
}

void dae::LifeDisplayComponent::UpdateText(const dae::PlayerComponent* component) const
{
	m_pTextComp->SetText(m_BaseText + std::to_string(component->GetHP()));
}
