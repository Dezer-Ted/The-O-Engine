#pragma once
#include "SceneManager.h"

namespace dae
{
	class GameObject;

	class Scene final {
		friend Scene& SceneManager::CreateScene(const std::string& name);

	public:
		void Add(std::shared_ptr<GameObject> object);
		void Remove(std::shared_ptr<GameObject> object);
		void RemoveAll();

		void FixedUpdate();
		void Update();
		void Render() const;
		void LateUpdate();
		void CleanUp();

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;
		bool   GetDestructionFlag() const;
		void   DestroyScene();

	private:
		explicit Scene(const std::string& name);

		std::string                              m_name;
		std::vector<std::shared_ptr<GameObject>> m_objects{};
		bool                                     m_DestructionFlag{false};
		static unsigned int                      m_idCounter;
	};
}
