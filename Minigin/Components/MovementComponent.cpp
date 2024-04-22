#include "MovementComponent.h"

#include "../Engine/DesignPatterns/Singleton.h"
#include "../Engine/DeltaTime.h"
#include "../Engine/DesignPatterns/Blackboard.h"


dae::MovementComponent::MovementComponent(GameObject* pParent) :
	BaseComponent{pParent}
{
}

void dae::MovementComponent::ApplyMovement(const glm::vec2& input)
{
	const auto lastPos = GetParent()->GetTransform().GetLocalPosition();
	if(m_LastPosition != lastPos)
		m_LastPosition = lastPos;

	GetParent()->Translate(input * (m_MovementSpeed * Singleton<DeltaTime>::GetInstance().GetDeltaTime()));

	MovementDirection newDirection{DetermineDirection(input)};
	if(newDirection != m_Direction)
	{
		m_Direction = newDirection;
		NotifyObservers(Utils::DirectionChanged,std::make_unique<ObserverEventData>(this));
	}
	if(m_LastDirection != input)
	{
		if(input == glm::vec2{0, 0})
		{
			NotifyObservers(Utils::MovementStopped, std::make_unique<ObserverEventData>(this));
		}
		if(m_LastDirection == glm::vec2{0, 0})
		{
			NotifyObservers(Utils::MovementStarted, std::make_unique<ObserverEventData>(this));
		}
	}

	m_LastDirection = input;
}

dae::MovementComponent::MovementDirection dae::MovementComponent::GetDirection() const
{
	return m_Direction;
}

void dae::MovementComponent::UndoMovement() const
{
	GetParent()->GetTransform().SetLocalPosition(m_LastPosition);
}

void dae::MovementComponent::Update()
{

}

::dae::MovementComponent::MovementDirection dae::MovementComponent::DetermineDirection(const glm::vec2& input)
{
	if(input.x > 0)
		return MovementDirection::Right;
	if(input.x < 0)
		return MovementDirection::Left;
	if(input.y < 0)
		return MovementDirection::Up;
	if(input.y > 0)
		return MovementDirection::Down;
	return MovementDirection::Down;
}
