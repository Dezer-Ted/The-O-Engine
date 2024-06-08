#include "SaveScoreCommand.h"

#include "../Components/NameSelectionComponent.h"

dae::SaveScoreCommand::SaveScoreCommand(dae::GameObject* pParent) : GameObjectCommand(pParent)
{
	m_pNameSelecComp = pParent->GetComponentByClass<NameSelectionComponent>();
}

void dae::SaveScoreCommand::Execute()
{
	m_pNameSelecComp->SaveHighScore();
}
