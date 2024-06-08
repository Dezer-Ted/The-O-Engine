#include "NameSelectionAction.h"

#include "../Components/NameSelectionComponent.h"

dae::NameSelectionAction::NameSelectionAction(GameObject* pParent) : GameObjectCommand(pParent)
{
	m_pNameSelectionComp = pParent->GetComponentByClass<NameSelectionComponent>();
}

void dae::NameSelectionAction::Execute2DAxis(const glm::vec2& input)
{
	if(input == glm::vec2{0, 0})
		return;
	if(input.x > 0)
	{
		m_pNameSelectionComp->MoveIndicatorRight();
	}
	else if(input.x < 0)
	{
		m_pNameSelectionComp->MoveIndicatorLeft();
	}
	else if(input.y > 0)
	{
		m_pNameSelectionComp->ScrollCurrentCharacterDown();
	}
	else if(input.y < 0)
	{
		m_pNameSelectionComp->ScrollCurrentCharacterUp();
	}
}
