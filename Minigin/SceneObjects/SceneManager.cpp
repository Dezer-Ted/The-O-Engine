#include "SceneManager.h"
#include "Scene.h"
#include "Time.h"
void dae::SceneManager::Update()
{
	for(auto& scene : m_scenes)
	{
		scene->Update();
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

void dae::SceneManager::LateUpdate()
{
	for(auto& scene : m_scenes)
    	{
    		scene->LateUpdate();
    	}
}

void dae::SceneManager::CleanUp()
{
	for(const auto& scene : m_scenes)
	{
		scene->CleanUp();
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}

void dae::SceneManager::FixedUpdate()
{
	for(auto& scene : m_scenes)
	{
		scene->FixedUpdate();
	}
}
