#include "BombAction.h"

#include "../Components/PlayerComponent.h"

dae::BombAction::BombAction(dae::GameObject* pOwner) : GameObjectCommand(pOwner)
{
	m_pPlayerComp = pOwner->GetComponentByClass<dae::PlayerComponent>();
}

void dae::BombAction::Execute()
{
	m_pPlayerComp->DropBomb();
}

