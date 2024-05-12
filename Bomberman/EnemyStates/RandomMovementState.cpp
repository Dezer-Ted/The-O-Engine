#include "RandomMovementState.h"


dae::RandomMovementState::~RandomMovementState()
{

}

void dae::RandomMovementState::HandleWallCollision()
{
	SetMovementDirection(GenerateRandomDirection());
}

bool dae::RandomMovementState::Update()
{
	return m_DirtyFlag;
}

glm::vec2 dae::RandomMovementState::GetMovementDirection()
{
	m_DirtyFlag = false;
	return m_MovementDirection;
}

glm::vec2 dae::RandomMovementState::GenerateRandomDirection() const
{

	while(true)
	{
		auto direction{m_Directions[rand() % m_Directions.size()]};
		if(direction != m_MovementDirection)
			return direction;
	}
}

void dae::RandomMovementState::SetMovementDirection(const glm::vec2& input)
{
	m_MovementDirection = input;
	m_DirtyFlag = true;
}
