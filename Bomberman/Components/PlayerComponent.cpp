#include "PlayerComponent.h"

#include "Components/SpriteComponent.h"

dae::PlayerComponent::PlayerComponent(GameObject* pParent)
	: BaseComponent(pParent)
{
	m_pSpriteComponent = GetParent()->GetComponentByClass<SpriteComponent>();
}

void dae::PlayerComponent::Notify(Utils::GameEvent event, BaseComponent* components)
{
	switch(event)
	{
	case Utils::DirectionChanged:
		{
			const auto moveComp = dynamic_cast<MovementComponent*>(components);
			if(moveComp) ChangeAnimation(moveComp->GetDirection());
		}
		break;
	case Utils::MovementStopped:
		{
			m_pSpriteComponent->ShouldUpdate(false);
		}
		break;
	case Utils::MovementStarted:
		{
			m_pSpriteComponent->ShouldUpdate(true);
		}
		break;
	}
}

void dae::PlayerComponent::ChangeAnimation(MovementComponent::MovementDirection direction)
{
	switch(direction)
	{
	case MovementComponent::MovementDirection::Up:
		m_pSpriteComponent->SwitchToSprite("WalkUp");
		break;
	case MovementComponent::MovementDirection::Down:
		m_pSpriteComponent->SwitchToSprite("WalkDown");
		break;
	case MovementComponent::MovementDirection::Left:
		m_pSpriteComponent->SwitchToSprite("WalkLeft");
		break;
	case MovementComponent::MovementDirection::Right:
		m_pSpriteComponent->SwitchToSprite("WalkRight");
		break;
	}
}
