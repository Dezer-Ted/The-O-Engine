#include "BaseState.h"

glm::vec2 dae::BaseState::GenerateRandomDirection()
{
	switch(rand() % 4)
	{
	case 0:
		return {1, 0};
	case 1:
		return {-1, 0};
	case 2:
		return {0, 1};
	case 3:
		return {0, -1};
	default:
		return {0, 0};
	}
}

dae::DirectionChangeEvent::DirectionChangeEvent(BaseComponent* component, const glm::vec2& direction) : ObserverEventData(component)
{
	m_Direction = direction;
}
