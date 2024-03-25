#include "MovementComponent.h"

#include "../Singleton.h"
#include "../DeltaTime.h"

dae::MovementComponent::MovementComponent(GameObject* pParent) :
	BaseComponent{pParent}
{
}

void dae::MovementComponent::ApplyMovement(const glm::vec2& direction)
{
	GetParent()->Translate(direction * (m_MovementSpeed * Singleton<DeltaTime>::GetInstance().GetDeltaTime()));
}
