#include "PowerUpPickUpComponent.h"

#include "Components/ColliderComponent.h"

dae::PowerUpPickUpComponent::PowerUpPickUpComponent(GameObject* pParent) : BaseComponent(pParent)
{

}

void dae::PowerUpPickUpComponent::SetPowerUp(PowerUps powerUp)
{
	m_PowerUps = powerUp;
}

dae::PowerUps dae::PowerUpPickUpComponent::GetPowerUp() const
{
	return m_PowerUps;
}

void dae::PowerUpPickUpComponent::Notify(Utils::GameEvent event, ObserverEventData* eventData)
{
	if(event == Utils::GameEvent::Collision)
	{
		const auto pCollisionEvent{dynamic_cast<CollisionEventData*>(eventData)};
		if(pCollisionEvent->m_OtherCollider->GetParentTag() != "Player")
			return;

		GetParent()->DestroyObject();

	}
}
