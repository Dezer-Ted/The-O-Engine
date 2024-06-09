#pragma once
#include <SDL_rect.h>
#include <string>
#include <vector>

#include "LevelData.h"


namespace dae
{
	class GridComponent;
	class GameObject;
	class Scene;

	enum class GameMode {
		Single,
		Versus,
		Coop
	};

	class LevelLoader final {
	public:
		static void            LoadLevel(const std::string& path);
		inline static GameMode m_GameMode{GameMode::Single};

	private:
		static LevelData      LoadLevelFromJson(const std::string levelPath);
		static GridComponent* InitGrid(Scene* pScene, const SDL_Rect& bounds, int itemAmount, float fillAmount);
		static void           InitEnemies(Scene* pScene, const std::vector<GameObject*>& players, const LevelData& levelData, GridComponent* gridComp);
	};
}
