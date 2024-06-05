#include "BaseTransition.h"

dae::StateTransitionEvent::StateTransitionEvent(BaseComponent* component, BaseState* toState)
	: ObserverEventData(component),
	  m_ToState(toState)
{
}

dae::BaseTransition::BaseTransition(BaseState* pFromState, BaseState* pToState)
	: Observable(),
	  m_pFromState(pFromState),
	  m_pToState(pToState)
{
}
