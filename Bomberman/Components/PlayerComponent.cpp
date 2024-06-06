#include "PlayerComponent.h"

#include "BombComponent.h"
#include "PowerUpComponent.h"
#include "Components/ColliderComponent.h"
#include "Components/SpriteComponent.h"
#include "../GridComponent.h"
#include "Rendering/Sprite.h"

dae::PlayerComponent::PlayerComponent(GameObject* pParent)
	: BaseComponent(pParent)
{
	m_pSpriteComponent = GetParent()->GetComponentByClass<SpriteComponent>();
	m_pMoveComp = GetParent()->GetComponentByClass<MovementComponent>();
	m_pPowerUpComp = GetParent()->GetComponentByClass<PowerUpComponent>();
}

void dae::PlayerComponent::Notify(Utils::GameEvent event, ObserverEventData* eventData)
{
	switch(event)
	{
	case Utils::GameEvent::DirectionChanged:
		{
			ChangeAnimation(m_pMoveComp->GetDirection());
		}
		break;
	case Utils::GameEvent::MovementStopped:
		{
			m_pSpriteComponent->ShouldUpdate(false);
		}
		break;
	case Utils::GameEvent::MovementStarted:
		{
			m_pSpriteComponent->ShouldUpdate(true);
		}
		break;
	case Utils::GameEvent::Collision:
		{
			const auto pCollisionEvent{dynamic_cast<CollisionEventData*>(eventData)};

			if(pCollisionEvent->m_OtherCollider->GetParentTag() == "Explosion")
			{
				#ifdef _DEBUG
				std::cout << "Player got hit\n";
				#endif
			}
		}
	}
}

void dae::PlayerComponent::DropBomb()
{
	if(static_cast<int>(m_Bombs.size()) >= m_pPowerUpComp->GetBombUpgrade() + 1)
		return;

	glm::vec2 pos = GetParent()->GetTransform().GetWorldPosition();
	pos.x += static_cast<float>(m_pSpriteComponent->GetCurrentSprite()->m_TargetWidth);
	pos.y += static_cast<float>(m_pSpriteComponent->GetCurrentSprite()->m_TargetHeight);
	auto gridCenter = m_pGrid->GetGridCellPosition(m_pGrid->GetGridCoordinate(pos));
	auto go = std::make_shared<GameObject>(GetParent()->GetParentScene());
	go->SetTag("Bomb");
	go->SetLayer("Obstacle");
	go->SetPosition(gridCenter.x, gridCenter.y);
	auto spriteComp = go->AddComponent<SpriteComponent>();
	spriteComp->AddSprite(3, 1, "Character/BombAnimation.png", "BombAnim");
	spriteComp->SetScale(3.f);
	auto collisionComp = go->AddComponent<ColliderComponent>();
	collisionComp->AdjustBoundsToSpriteSize();
	auto bombComp{go->AddComponent<BombComponent>()};
	bombComp->Init(m_pGrid, m_pGrid->GetGridCoordinate(pos), this);
	bombComp->SetExplosionRange(m_pPowerUpComp->GetFireUpgrade());
	m_pMoveComp->EnableWalkThroughBombs();
	bombComp->AddObserver(m_pMoveComp);
	collisionComp->AddObserver(bombComp);
	GetParent()->GetParentScene()->Add(go);
	m_Bombs.push_back(go.get());
}

void dae::PlayerComponent::SetGrid(GridComponent* pGrid)
{
	m_pGrid = pGrid;
}

void dae::PlayerComponent::DetonateBombs() const
{
	if(!m_pPowerUpComp->GetDetonatorUpgrade())
		return;

	for(auto bomb : m_Bombs)
	{
		if(bomb == nullptr)
			continue;
		bomb->GetComponentByClass<BombComponent>()->Explode();
	}
}

void dae::PlayerComponent::RemoveExplodedBomb(GameObject* toBeRemoved)
{
	auto it = std::remove(m_Bombs.begin(), m_Bombs.end(), toBeRemoved);
	if(it != m_Bombs.end())
		m_Bombs.erase(it);
}

void dae::PlayerComponent::ChangeAnimation(MovementComponent::MovementDirection direction) const
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
