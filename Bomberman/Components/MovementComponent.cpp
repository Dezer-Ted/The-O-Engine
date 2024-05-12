#include "MovementComponent.h"

#include "Engine/DesignPatterns/Singleton.h"
#include "Engine/DeltaTime.h"
#include "Engine/DesignPatterns/Blackboard.h"


dae::MovementComponent::MovementComponent(GameObject* pParent) :
	BaseComponent{pParent}
{
}

void dae::MovementComponent::ApplyMovement(const glm::vec2& input)
{

	MovementDirection newDirection{DetermineDirection(input)};
	const auto        lastPos = GetParent()->GetTransform().GetLocalPosition();
	if(m_LastPosition != lastPos)
		m_LastPosition = lastPos;
	if(m_IsDodging)
	{
		DodgeWalls(input);
	}
	else
	{
		GetParent()->Translate(input * (m_MovementSpeed * Singleton<DeltaTime>::GetInstance().GetDeltaTime()));
	}

	if(newDirection != m_Direction)
	{
		m_Direction = newDirection;
		NotifyObservers(Utils::DirectionChanged, std::make_unique<ObserverEventData>(this));
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

void dae::MovementComponent::SetSpeed(float movementSpeed)
{
	m_MovementSpeed = movementSpeed;
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

void dae::MovementComponent::DodgeWalls(const glm::vec2& input)
{
	glm::vec2 adjustedInput{normalize((input + m_DodgeDirection))};
	GetParent()->Translate(adjustedInput * (m_MovementSpeed * Singleton<DeltaTime>::GetInstance().GetDeltaTime()));
	m_IsDodging = false;

}

void dae::MovementComponent::DodgeYCheck(const SDL_Rect& bounds, const glm::vec2& playerCenter, float bufferRange)
{
	if(static_cast<float>(bounds.y) + bufferRange < playerCenter.y)
	{
		m_IsDodging = true;
		m_DodgeDirection = glm::vec2{0, 1};
	}
	else if(static_cast<float>(bounds.y + bounds.h) - bufferRange < playerCenter.y)
	{
		m_IsDodging = true;
		m_DodgeDirection = glm::vec2{0, -1};
	}
	else
	{
		UndoMovement();
	}
}

void dae::MovementComponent::DodgeXCheck(const SDL_Rect& bounds, const glm::vec2& playerCenter, float bufferRange)
{
	if(static_cast<float>(bounds.x) + bufferRange < playerCenter.x)
	{
		m_IsDodging = true;
		m_DodgeDirection = glm::vec2{-1, 0};
	}
	else if(static_cast<float>(bounds.x + bounds.w) - bufferRange < playerCenter.x)
	{
		m_IsDodging = true;
		m_DodgeDirection = glm::vec2{1, 0};
	}
	else
	{
		UndoMovement();
	}
}

void dae::MovementComponent::HandleCollision(dae::ObserverEventData* eventData)
{
	if(eventData == nullptr)
		return;
	auto pCollisionEvent{dynamic_cast<CollisionEventData*>(eventData)};
	if(pCollisionEvent->m_OtherCollider->GetParentTag() == "Wall")
	{
		auto      bounds{pCollisionEvent->m_OtherCollider->GetBounds()};
		auto      ownBounds{dynamic_cast<ColliderComponent*>(pCollisionEvent->m_Component)->GetBounds()};
		float     bufferRange{static_cast<float>(bounds.w) * 0.2f};
		glm::vec2 playerCenter{ownBounds.x + ownBounds.w / 2, ownBounds.y + ownBounds.h / 2};
		switch(m_Direction)
		{
		case MovementDirection::Up:
		case MovementDirection::Down:
			DodgeXCheck(bounds, playerCenter, bufferRange);
			break;
		case MovementDirection::Left:
		case MovementDirection::Right:
			DodgeYCheck(bounds, playerCenter, bufferRange);
			break;
		default:
			break;
		}
	}
}

void dae::MovementComponent::Notify(Utils::GameEvent event, ObserverEventData* eventData)
{
	if(event == Utils::Collision)
	{
		//HandleCollision(eventData);
		UndoMovement();
	}
}
