#include "SightedTransition.h"

#include "../../GridComponent.h"

dae::SightedTransition::SightedTransition(BaseState* pFromState, BaseState* pToState, GameObject* pPlayer, GameObject* pParent, GridComponent* pGrid,
                                          bool       invertCondition)
	: BaseTransition(pFromState, pToState),
	  m_pPlayer(pPlayer),
	  m_pParent(pParent),
	  m_pGrid(pGrid),
	  m_ConditionInverted(invertCondition)
{
}

void dae::SightedTransition::CheckExitCondition()
{
	DetectPlayerAlignment();
}

void dae::SightedTransition::DetectPlayerAlignment()
{
	const CellCoordinate playerGridPos{m_pGrid->GetGridCoordinate(m_pPlayer->GetTransform().GetWorldPosition())};
	const CellCoordinate parentGridPos{m_pGrid->GetGridCoordinate(m_pParent->GetTransform().GetWorldPosition())};
	if(playerGridPos.x == parentGridPos.x)
	{
		DetermineDirection(Alignment::Horizontal, parentGridPos.y, playerGridPos.y, playerGridPos.x);
	}
	else if(playerGridPos.y == parentGridPos.y)
	{
		DetermineDirection(Alignment::Vertical, parentGridPos.x, playerGridPos.x, playerGridPos.y);
	}
}

void dae::SightedTransition::DetermineDirection(Alignment alignment, int start, int end, int alignedLine)
{
	for(int i = 0; i < abs(start - end); ++i)
	{
		if(start - end > 0)
		{
			if(CheckIfObscured(alignment, alignedLine, i, start, true))
			{
				if(!m_ConditionInverted)
					return;
				NotifyObservers(Utils::GameEvent::TransitionState, std::make_unique<StateTransitionEvent>(nullptr, GetToState()));
			}
		}
		else
		{
			if(CheckIfObscured(alignment, alignedLine, i, start, false))
			{
				if(!m_ConditionInverted)
					return;
				NotifyObservers(Utils::GameEvent::TransitionState, std::make_unique<StateTransitionEvent>(nullptr, GetToState()));
			}
		}
	}
	if(!m_ConditionInverted)
		NotifyObservers(Utils::GameEvent::TransitionState, std::make_unique<StateTransitionEvent>(nullptr, GetToState()));
}

bool dae::SightedTransition::CheckIfObscured(Alignment alignment, int alignedLine, int offset, int start, bool isPositiv)
{
	if(isPositiv)
		offset *= -1;
	switch(alignment)
	{
	case Alignment::Horizontal:
		{
			CellCoordinate horizontalCoords{alignedLine, start + offset};
			if(m_pGrid->GetWallstateAtPos(horizontalCoords) != WallState::open)
				return true;
			break;
		}
	case Alignment::Vertical:
		{
			CellCoordinate verticalCoords{start + offset, alignedLine};
			if(m_pGrid->GetWallstateAtPos(verticalCoords) != WallState::open)
				return true;
			break;
		}
	}
	return false;

}
