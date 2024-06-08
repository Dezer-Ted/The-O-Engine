#include "SkipLevelCommand.h"

#include "../SceneNavigator.h"

dae::SkipLevelCommand::SkipLevelCommand(GameObject* pParent) : GameObjectCommand(pParent)
{
}

void dae::SkipLevelCommand::Execute()
{
	SceneNavigator::UnloadStage();
}
