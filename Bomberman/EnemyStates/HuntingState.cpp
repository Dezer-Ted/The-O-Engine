#include "HuntingState.h"

#include "../GridComponent.h"

dae::HuntingState::HuntingState(GameObject* pPlayer, GridComponent* pGrid, GameObject* pParent)
	: BaseState(pParent),
	  m_pGridComp(pGrid),
	  m_pPlayer(pPlayer)
{
}

void dae::HuntingState::Update()
{

}


void dae::HuntingState::OnEnter()
{
	const glm::vec2 playerPos{m_pPlayer->GetTransform().GetLocalPosition()};
	DetermineWalkDirection(playerPos);
}

void dae::HuntingState::DetermineWalkDirection(const glm::vec2& playerPos)
{
	const CellCoordinate playerGridPos{m_pGridComp->GetGridCoordinate(playerPos)};
	const CellCoordinate enemyGridPos{m_pGridComp->GetGridCoordinate(GetParent()->GetTransform().GetWorldPosition())};
	glm::vec2            distanceBetween{playerGridPos.x - enemyGridPos.x, playerGridPos.y - enemyGridPos.y};
	glm::vec2            walkDirection{};
	distanceBetween = normalize(distanceBetween);
	if(abs(distanceBetween.x) > abs(distanceBetween.y))
	{
		if(distanceBetween.x > 0)
			walkDirection = glm::vec2{1, 0};
		else
			walkDirection = glm::vec2{-1, 0};
	}
	else
	{
		if(distanceBetween.y > 0)
			walkDirection = glm::vec2{0, 1};
		else
			walkDirection = glm::vec2{0, -1};
	}
	NotifyObservers(Utils::GameEvent::DirectionChanged, std::make_unique<DirectionChangeEvent>(nullptr, walkDirection));
	m_Direction = walkDirection;
}
