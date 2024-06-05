#include "RandomWalkState.h"

#include "Components/ColliderComponent.h"
#include "Engine/DeltaTime.h"
#include "Engine/DesignPatterns/Singleton.h"
#include "Engine/DeltaTime.h"


dae::RandomWalkState::RandomWalkState(GameObject* pParent)
	: BaseState(pParent)
{

}

void dae::RandomWalkState::Update()
{
	if(!m_HasTurned)
		return;

	m_CurrentCooldown += Singleton<DeltaTime>::GetInstance().GetDeltaTime();

	if(m_CurrentCooldown <= m_TurnCooldown)
		return;

	m_HasTurned = false;
	m_CurrentCooldown = 0;
}

void dae::RandomWalkState::GenerateUnusedDirection()
{
	glm::vec2 direction{};
	do
	{
		direction = GenerateRandomDirection();
	}
	while(direction == m_Direction);
	m_Direction = direction;
	NotifyObservers(Utils::GameEvent::DirectionChanged, std::make_unique<DirectionChangeEvent>(nullptr, m_Direction));
}

void dae::RandomWalkState::Notify(Utils::GameEvent event, ObserverEventData* eventData)
{
	if(event != Utils::GameEvent::Collision)
		return;

	if(m_HasTurned)
		return;

	const auto pCollisionEvent{dynamic_cast<CollisionEventData*>(eventData)};

	if(pCollisionEvent->m_OtherCollider->GetParentObject()->GetLayer() != "Obstacle")
		return;

	m_HasTurned = true;
	GetParent()->Translate(-m_Direction * 3.f);
	GenerateUnusedDirection();
}

void dae::RandomWalkState::OnEnter()
{
	GenerateUnusedDirection();
}
