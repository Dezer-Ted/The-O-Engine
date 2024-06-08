#include "MenuNavigateCommand.h"

#include "../Components/MenuNavigatorComponent.h"

dae::MenuNavigateCommand::MenuNavigateCommand(GameObject* pParent) : GameObjectCommand(pParent)
{
	m_MenuComp = pParent->GetComponentByClass<MenuNavigatorComponent>();

}

void dae::MenuNavigateCommand::Execute2DAxis(const glm::vec2& input)
{
	if(input == glm::vec2{0, 0})
		return;
	if(input.y > 0)
	{
		m_MenuComp->MoveDown();
	}
	else if(input.y < 0)
	{
		m_MenuComp->MoveUp();
	}

}
