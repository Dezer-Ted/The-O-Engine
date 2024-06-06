#pragma once
#include <SDL_rect.h>
#include <string>

#include "LevelData.h"


namespace dae
{
	class GridComponent;
	class GameObject;
	class Scene;

	class LevelLoader final {
	public:
		static void LoadLevel(const std::string& path);

	private:
		static LevelData LoadLevelFromJson(const std::string levelPath);
		static GridComponent* InitGrid(Scene* pScene, const SDL_Rect& bounds, int itemAmount, float fillAmount);
		static void           InitEnemies(Scene* pScene, GameObject* pPlayer, const LevelData& levelData, GridComponent* gridComp);
	};
}
