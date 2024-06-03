#include "WallComponent.h"
#include "Components/SpriteComponent.h"

dae::WallComponent::WallComponent(GameObject* pOwner) : BaseComponent(pOwner)
{
	m_pSpriteComponent = pOwner->GetComponentByClass<SpriteComponent>();
}

void dae::WallComponent::StartDestruction()
{
	m_pSpriteComponent->SwitchToSprite("DestructionAnimation");
	m_IsDestroyed = true;
}

void dae::WallComponent::Notify(Utils::GameEvent event, ObserverEventData* eventData)
{
	switch(event)
	{
	case Utils::AnimationEnded:
		if(m_IsDestroyed)
			GetParent()->DestroyObject();
		break;
	}
}
