#include "ScoreDisplayComponent.h"

#include "PlayerComponent.h"
#include "../ResourceManager.h"
#include "TextComponent.h"
dae::ScoreDisplayComponent::ScoreDisplayComponent(GameObject* pParent) : BaseComponent(pParent)
{
	m_pTextComp = pParent->AddComponent<TextComponent>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	m_pTextComp->SetText(m_BaseString + "0", font, {255, 255, 255, 255});
}

void dae::ScoreDisplayComponent::Notify(Utils::GameEvent event, BaseComponent* components)
{
	switch(event)
	{
	case Utils::GameEvent::PlayerGainedPoints:
		const PlayerComponent* playerComp{dynamic_cast<PlayerComponent*>(components)};
		if(playerComp)
			UpdateText(playerComp);
		if(playerComp->GetScore()>= 500)
		break;
	}
}

void dae::ScoreDisplayComponent::UpdateText(const PlayerComponent* component) const
{
	m_pTextComp->SetText(m_BaseString+ std::to_string(component->GetScore()));
}
