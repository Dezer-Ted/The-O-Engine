#include "SceneNavigator.h"

#include "Input/InputManager.h"
#include "SceneObjects/SceneManager.h"
#include "SceneUtils/LevelLoader.h"

void dae::SceneNavigator::UnloadStage()
{
	if(m_LevelIndex >= 2)
		return;
	SceneManager::GetInstance().RemoveScene("Level" + std::to_string(m_LevelIndex));
	++m_LevelIndex;
	InputManager::GetInstance().WipeActions();
	m_IsUnloaded = true;
	m_LevelCompleted = true;
}

void dae::SceneNavigator::LoadStage()
{
	if(!m_IsUnloaded)
		return;

	dae::LevelLoader::LoadLevel("LevelData/Level" + std::to_string(m_LevelIndex) + ".json");
	m_IsUnloaded = false;
	m_LevelCompleted = false;
}

void dae::SceneNavigator::ReloadStage()
{
	SceneManager::GetInstance().RemoveScene("Level" + std::to_string(m_LevelIndex));
	InputManager::GetInstance().WipeActions();
	m_IsUnloaded = true;
}
