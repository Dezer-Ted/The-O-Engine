#include "MenuSelectCommand.h"

#include "../Components/MenuNavigatorComponent.h"

dae::MenuSelectCommand::MenuSelectCommand(dae::GameObject* pParent) : GameObjectCommand(pParent)
{
	m_pNavComp = pParent->GetComponentByClass<MenuNavigatorComponent>();
}

void dae::MenuSelectCommand::Execute()
{
	m_pNavComp->ExecuteCurrentlySelected();
}
