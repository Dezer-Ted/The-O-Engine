#include "EnemyComponent.h"

#include "MovementComponent.h"
#include "../EnemyStates/RandomWalkState.h"
#include "Components/ColliderComponent.h"
#include "Components/SpriteComponent.h"

dae::EnemyDiedEvent::EnemyDiedEvent(BaseComponent* comp, EnemyType type)
	: ObserverEventData(comp),
	  m_Type(type)
{
}

dae::EnemyComponent::EnemyComponent(GameObject* pParent) : BaseComponent(pParent)
{
	m_pMoveComp = pParent->GetComponentByClass<MovementComponent>();
	m_pSpriteComp = pParent->GetComponentByClass<SpriteComponent>();
}

void dae::EnemyComponent::Notify(Utils::GameEvent event, ObserverEventData* eventData)
{
	switch(event)
	{
	case Utils::GameEvent::DirectionChanged:
		{
			auto directionEvent{dynamic_cast<DirectionChangeEvent*>(eventData)};
			m_Direction = directionEvent->m_Direction;
			break;
		}
	case Utils::GameEvent::Collision:
		{
			auto collisionEvent{dynamic_cast<CollisionEventData*>(eventData)};
			if(collisionEvent->m_OtherCollider->GetParentTag() != "Explosion")
				return;
			m_IsDying = true;
			m_pSpriteComp->SwitchToSprite("DeathAnim");
			break;
		}
	case Utils::GameEvent::TransitionState:
		{
			auto transitionEvent{dynamic_cast<StateTransitionEvent*>(eventData)};
			SetState(transitionEvent->m_ToState);
			break;
		}
	case Utils::GameEvent::AnimationEnded:
		{
			if(!m_IsDying)
				return;
			GetParent()->DestroyObject();
			NotifyObservers(Utils::GameEvent::EnemyDied, std::make_unique<EnemyDiedEvent>(nullptr, m_Type));
		}
	}
}

void dae::EnemyComponent::Update()
{
	if(m_IsDying)
		return;
	m_pCurrentState->Update();
	for(auto transition : m_ActiveTransitions)
	{
		transition->CheckExitCondition();
	}
	m_pMoveComp->ApplyMovement(m_Direction);
}

dae::BaseState* dae::EnemyComponent::AddState(std::unique_ptr<BaseState> state)
{
	state->AddObserver(this);
	m_States.push_back(std::move(state));
	return m_States.back().get();
}

dae::BaseTransition* dae::EnemyComponent::AddTransition(std::unique_ptr<BaseTransition> transition)
{
	transition->AddObserver(this);
	m_Transitions.push_back(std::move(transition));
	return m_Transitions.back().get();
}

void dae::EnemyComponent::SetActiveTransitions()
{
	m_ActiveTransitions.clear();
	for(const auto& transition : m_Transitions)
	{
		if(transition->GetFromState() != m_pCurrentState)
			continue;
		transition->ResetTransition();
		m_ActiveTransitions.push_back(transition.get());
	}
}

void dae::EnemyComponent::SetState(BaseState* pState)
{
	if(m_pCurrentState != nullptr)
		m_pCurrentState->OnExit();
	m_pCurrentState = pState;
	m_pCurrentState->OnEnter();

	m_Direction = m_pCurrentState->GetDirection();
	SetActiveTransitions();
}

void dae::EnemyComponent::SetEnemyType(EnemyType type)
{
	m_Type = type;
}
