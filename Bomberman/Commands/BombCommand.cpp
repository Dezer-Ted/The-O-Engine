#include "BombCommand.h"

#include "../Components/PlayerComponent.h"

dae::BombCommand::BombCommand(dae::GameObject* pOwner) : GameObjectCommand(pOwner)
{
	m_pPlayerComp = pOwner->GetComponentByClass<dae::PlayerComponent>();
}

void dae::BombCommand::Execute()
{
	m_pPlayerComp->DropBomb();
}



