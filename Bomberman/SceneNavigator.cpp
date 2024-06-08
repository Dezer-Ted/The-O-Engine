#include "SceneNavigator.h"

#include "EnemyTracker.h"
#include "Input/InputManager.h"
#include "SceneObjects/SceneManager.h"
#include "SceneUtils/LevelLoader.h"
#include "SceneUtils/MenuLoader.h"

void dae::SceneNavigator::UnloadStage()
{
	EnemyTracker::GetInstance().ResetEnemies();
	if(m_LevelIndex < 0)
	{
		SceneManager::GetInstance().RemoveScene("StartScreen");
	}
	else if(m_LevelIndex == 3)
	{
		SceneManager::GetInstance().RemoveScene("EndScreen");
	}
	else
	{
		SceneManager::GetInstance().RemoveScene("Level" + std::to_string(m_LevelIndex));
	}
	++m_LevelIndex;
	InputManager::GetInstance().WipeActions();
	m_IsUnloaded = true;
	m_LevelCompleted = true;
}

void dae::SceneNavigator::LoadStage()
{
	if(!m_IsUnloaded)
		return;
	if(m_LevelIndex == 3)
	{
		dae::MenuLoader::LoadEndScreen();
	}
	else if(m_LevelIndex == 4)
	{
		dae::MenuLoader::LoadStartScreen();
		m_LevelIndex = -1;
	}
	else
	{
		dae::LevelLoader::LoadLevel("LevelData/Level" + std::to_string(m_LevelIndex) + ".json");
	}
	m_IsUnloaded = false;
	m_LevelCompleted = false;
}

void dae::SceneNavigator::ReloadStage()
{
	SceneManager::GetInstance().RemoveScene("Level" + std::to_string(m_LevelIndex));
	InputManager::GetInstance().WipeActions();
	m_IsUnloaded = true;
}
