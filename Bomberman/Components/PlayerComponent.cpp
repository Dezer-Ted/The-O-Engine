#include "PlayerComponent.h"

#include "BombComponent.h"
#include "Components/ColliderComponent.h"
#include "Components/SpriteComponent.h"
#include "Engine/DesignPatterns/Blackboard.h"
#include "../Grid.h"

dae::PlayerComponent::PlayerComponent(GameObject* pParent)
	: BaseComponent(pParent)
{
	m_pSpriteComponent = GetParent()->GetComponentByClass<SpriteComponent>();
	m_pMoveComp = GetParent()->GetComponentByClass<MovementComponent>();
}

void dae::PlayerComponent::Notify(Utils::GameEvent event, std::unique_ptr<ObserverEventData> eventData)
{
	switch(event)
	{
	case Utils::DirectionChanged:
		{
			ChangeAnimation(m_pMoveComp->GetDirection());
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
	case Utils::Collision:
		{
			auto pCollisionEvent{dynamic_cast<CollisionEventData*>(eventData.get())};
			if(pCollisionEvent->m_OtherCollider->GetParentTag() == "Wall")
			{
				m_pMoveComp->UndoMovement();
			}
		}
	}
}

void dae::PlayerComponent::DropBomb()
{
	glm::vec2 pos = GetParent()->GetTransform().GetWorldPosition();
	auto      gridCenter = m_pGrid->GetGridCellPosition(pos);
	auto      go = std::make_shared<GameObject>(GetParent()->GetParentScene());
	go->SetTag("Bomb");
	go->SetPosition(pos.x, pos.y);
	auto spriteComp = go->AddComponent<SpriteComponent>();
	spriteComp->AddSprite(3, 1, "Character/BombAnimation.png", "BombAnim");
	spriteComp->SetScale(3.f);
	auto collisionComp = go->AddComponent<ColliderComponent>();
	collisionComp->AdjustBoundsToSpriteSize();
	//go->AddComponent<BombComponent>();
	GetParent()->GetParentScene()->Add(go);
}

void dae::PlayerComponent::SetGrid(Grid* pGrid)
{
	m_pGrid = pGrid;
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
