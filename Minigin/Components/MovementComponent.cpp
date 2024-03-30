#include "MovementComponent.h"

#include "../Singleton.h"
#include "../DeltaTime.h"


dae::MovementComponent::MovementComponent(GameObject* pParent) :
	BaseComponent{pParent}
{
}

void dae::MovementComponent::ApplyMovement(const glm::vec2& input)
{
	GetParent()->Translate(input * (m_MovementSpeed * Singleton<DeltaTime>::GetInstance().GetDeltaTime()));

	MovementDirection newDirection{DetermineDirection(input)};
	if(newDirection != m_Direction)
	{
		m_Direction = newDirection;
		NotifyObservers(Utils::DirectionChanged, this);
	}
	if(m_LastDirection != input)
	{
		if(input == glm::vec2{0, 0})
		{
			NotifyObservers(Utils::MovementStopped, this);
		}
		if(m_LastDirection == glm::vec2{0, 0})
		{
			NotifyObservers(Utils::MovementStarted, this);
		}
	}

	m_LastDirection = input;
}

dae::MovementComponent::MovementDirection dae::MovementComponent::GetDirection()
{
	return m_Direction;
}

::dae::MovementComponent::MovementDirection dae::MovementComponent::DetermineDirection(const glm::vec2& input)
{
	if(input.x > 0) return MovementDirection::Right;
	if(input.x < 0) return MovementDirection::Left;
	if(input.y < 0) return MovementDirection::Up;
	if(input.y > 0) return MovementDirection::Down;
	return MovementDirection::Down;
}
