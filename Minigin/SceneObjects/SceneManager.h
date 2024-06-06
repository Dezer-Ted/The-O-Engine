#pragma once
#include <vector>
#include <string>
#include <memory>
#include "../Engine/DesignPatterns/Singleton.h"
#include "Scene.h"

namespace dae
{
	class SceneManager final : public Singleton<SceneManager> {
	public:
		Scene* CreateScene(const std::string& name);
		void   LoadScene(const std::string& name);
		void   FixedUpdate();
		void   Update();
		void   LateUpdate();
		void   Render();
		void   CleanUp();
		~SceneManager() override;

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_scenes;
		Scene*                              m_pCurrentScene{nullptr};
	};
}
