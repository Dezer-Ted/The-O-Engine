#pragma once
#include "SceneObjects/Scene.h"
#include "../HighScoreListComponent.h"

namespace dae
{
	class MenuLoader {
	public:
		static void LoadStartScreen();
		static void LoadEndScreen();

	private:
		static void                    LoadLogo(dae::Scene* pScene);
		static void                    LoadModes(dae::Scene* pScene);
		static void                    CreateNameSelection(Scene* pScene);
	};
}
