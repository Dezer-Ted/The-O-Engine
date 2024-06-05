#include "CooldownTransition.h"

#include "Engine/DeltaTime.h"
#include "Engine/DesignPatterns/Singleton.h"

dae::CooldownTransition::CooldownTransition(BaseState* pFromState, BaseState* pToState, float cooldown)
	: BaseTransition(pFromState, pToState),
	  m_Cooldown(cooldown)
{
}

void dae::CooldownTransition::CheckExitCondition()
{
	m_CurrentCooldown += Singleton<DeltaTime>::GetInstance().GetDeltaTime();
	if(m_CurrentCooldown >= m_Cooldown)
	{
		m_CurrentCooldown = 0;
		NotifyObservers(Utils::GameEvent::TransitionState, std::make_unique<StateTransitionEvent>(nullptr, GetToState()));
	}

}

void dae::CooldownTransition::ResetTransition()
{
	m_CurrentCooldown = 0.f;
}
