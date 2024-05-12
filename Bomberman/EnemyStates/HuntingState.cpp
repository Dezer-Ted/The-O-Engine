#include "HuntingState.h"

#include "../GridComponent.h"
#include "../Components/OnealComponent.h"

void dae::HuntingState::HandleWallCollision()
{

}

bool dae::HuntingState::Update()
{

	return m_DirtyFlag;
}

glm::vec2 dae::HuntingState::GetMovementDirection()
{
	m_DirtyFlag = false;
	return m_Direction;
}

dae::HuntingState::~HuntingState()
{
}

void dae::HuntingState::Notify(Utils::GameEvent event, dae::ObserverEventData* eventData)
{
	if(event == Utils::PlayerSighted)
	{
		auto      sightedData{dynamic_cast<SightedEventData*>(eventData)};
		glm::vec2 directionF{normalize((sightedData->m_Playerpos - sightedData->m_EnemyPos))};
		SetDirection({static_cast<int>(directionF.x), static_cast<int>(directionF.y)});
	}
}

void dae::HuntingState::SetDirection(const glm::vec2 direction)
{
	m_Direction = direction;
	m_DirtyFlag = true;
}
