#include "OnealComponent.h"
#include "SceneObjects/GameObject.h"
#include "MovementComponent.h"
#include "../GridComponent.h"
#include "Components/ColliderComponent.h"
#include "Engine/ObserverEventData.h"
#include "../EnemyStates/RandomMovementState.h"
#include "../EnemyStates/BaseState.h"
#include "Engine/DeltaTime.h"
#include "Engine/DesignPatterns/Singleton.h"

dae::SightedEventData::SightedEventData(BaseComponent* component, const glm::vec2& playerGridPos, GridComponent* pGrid, const glm::vec2& enemyPos)
	: ObserverEventData(component)
	  , m_Playerpos(playerGridPos)
	  , m_pGrid(pGrid)
	  , m_EnemyPos(enemyPos)
{

}

dae::OnealComponent::OnealComponent(GameObject* pParent) : BaseComponent(pParent)
{
	m_pMoveComp = pParent->GetComponentByClass<MovementComponent>();
	m_pCurrentState = m_pRandomMovementState.get();
	m_pCurrentState->HandleWallCollision();
	m_WalkDirection = m_pCurrentState->GetMovementDirection();
}

dae::OnealComponent::~OnealComponent()
{
}

void dae::OnealComponent::Notify(Utils::GameEvent event, ObserverEventData* eventData)
{
	if(event == Utils::Collision)
	{
		auto colliderData{dynamic_cast<CollisionEventData*>(eventData)};
		if(colliderData->m_OtherCollider->GetParentTag() == "Wall")
		{
			m_pCurrentState->HandleWallCollision();
			glm::vec2 pos{GetParent()->GetTransform().GetWorldPosition()};
			pos.x -= m_WalkDirection.x * 3;
			pos.y -= m_WalkDirection.y * 3;

			GetParent()->GetTransform().SetLocalPosition({pos, 0});
		}
	}
}

void dae::OnealComponent::Update()
{
	if(m_pCurrentState->Update() && m_CurrentCooldown > m_DirectionChangeCooldown)
	{
		m_CurrentCooldown = 0.f;
		m_WalkDirection = m_pCurrentState->GetMovementDirection();
	}
	m_CurrentCooldown += Singleton<DeltaTime>::GetInstance().GetDeltaTime();
	m_CurrentHuntLength += Singleton<DeltaTime>::GetInstance().GetDeltaTime();
	if(m_CurrentHuntLength >= m_HuntingDuration)
	{
		m_pCurrentState = m_pRandomMovementState.get();
		m_CurrentHuntLength = 0.f;
	}
	m_pMoveComp->ApplyMovement(m_WalkDirection);
	IsPlayerInSight();
}

void dae::OnealComponent::Initialize(GridComponent* pGrid, GameObject* pPlayer)
{
	m_pGridComp = pGrid;
	m_pPlayer = pPlayer;
	AddObserver(m_pHuntingState.get());
}

void dae::OnealComponent::IsPlayerInSight()
{
	glm::vec2 gridPos{m_pGridComp->GetGridCoordinate(GetParent()->GetTransform().GetLocalPosition())};
	glm::vec2 playerGridPos{m_pGridComp->GetGridCoordinate(m_pPlayer->GetTransform().GetWorldPosition())};
	if(static_cast<int>(gridPos.x) == static_cast<int>(playerGridPos.x) || static_cast<int>(gridPos.y) == static_cast<int>(playerGridPos.y))
	{
		std::cout << "Sighted\n";
		NotifyObservers(Utils::PlayerSighted,
		                std::make_unique<SightedEventData>(this, playerGridPos, m_pGridComp,
		                                                   m_pGridComp->GetGridCoordinate(GetParent()->GetTransform().GetWorldPosition())));
		m_pCurrentState = m_pHuntingState.get();
		m_CurrentHuntLength = 0.f;
	}

}
