#include "VersusPlayerComponent.h"

#include "MovementComponent.h"
#include "Components/ColliderComponent.h"
#include "Components/SpriteComponent.h"
#include "Input/InputManager.h"

dae::VersusPlayerComponent::VersusPlayerComponent(GameObject* pParent) : BaseComponent(pParent)
{
	m_pSpriteComp = pParent->GetComponentByClass<SpriteComponent>();
	m_pMoveComp = pParent->GetComponentByClass<MovementComponent>();
	m_pSpriteComp->AddObserver(this);
}

void dae::VersusPlayerComponent::Notify(Utils::GameEvent event, ObserverEventData* eventData)
{
	if(event == Utils::GameEvent::Collision)
	{
		auto pCollisionData{dynamic_cast<CollisionEventData*>(eventData)};
		if(pCollisionData->m_OtherCollider->GetParentTag() == "Explosion")
		{
			m_pSpriteComp->SwitchToSprite("DeathAnim");
			m_pMoveComp->CanWalk(false);
			m_IsDead = true;
		}
	}
	else if(event == Utils::GameEvent::AnimationEnded)
	{
		if(!m_IsDead)
			return;
		GetParent()->DestroyObject();
		InputManager::GetInstance().RemoveActionsByGameObject(GetParent());
		NotifyObservers(Utils::GameEvent::PlayerDied, nullptr);
	}
}
