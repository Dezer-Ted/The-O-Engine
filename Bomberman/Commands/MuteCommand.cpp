#include "MuteCommand.h"

#include "Engine/DesignPatterns/ServiceLocator.h"

MuteCommand::MuteCommand(dae::GameObject* pParent) : GameObjectCommand(pParent)
{
}

void MuteCommand::Execute()
{
	dae::ServiceLocator::GetSoundSystem()->MuteSoundSystem();
}
