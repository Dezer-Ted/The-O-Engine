#include "SceneManager.h"
#include "Scene.h"
#include "Time.h"

void dae::SceneManager::Update()
{
	m_pCurrentScene->Update();
}

void dae::SceneManager::Render()
{
	m_pCurrentScene->Render();
}

void dae::SceneManager::LateUpdate()
{
	m_pCurrentScene->LateUpdate();
}

void dae::SceneManager::CleanUp()
{
	for(const auto& scene : m_scenes)
	{
		scene->CleanUp();
	}
}

dae::SceneManager::~SceneManager()
{
}


dae::Scene* dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::make_shared<Scene>(name);
	m_scenes.push_back(std::move(scene));
	return scene.get();
}

void dae::SceneManager::LoadScene(const std::string& name)
{
	for(auto& scene : m_scenes)
	{
		if(scene->GetSceneName() == name)
			m_pCurrentScene = scene.get();
	}
}

void dae::SceneManager::FixedUpdate()
{
	m_pCurrentScene->FixedUpdate();
}
