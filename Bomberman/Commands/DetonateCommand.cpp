#include "DetonateCommand.h"

#include "../Components/PlayerComponent.h"

void dae::DetonateCommand::Execute()
{
	m_pPlayerComponent->DetonateBombs();
}

dae::DetonateCommand::DetonateCommand(GameObject* pOwner) : GameObjectCommand(pOwner)
{
	m_pPlayerComponent = pOwner->GetComponentByClass<PlayerComponent>();
}
