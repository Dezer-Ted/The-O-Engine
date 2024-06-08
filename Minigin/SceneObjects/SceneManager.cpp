#include "SceneManager.h"
#include "Scene.h"
#include "Time.h"
#include "../../Bomberman/SceneNavigator.h"

void dae::SceneManager::Update()
{
	if(m_pCurrentScene == nullptr)
		return;
	m_pCurrentScene->Update();
}

void dae::SceneManager::Render()
{
	if(m_pCurrentScene == nullptr)
		return;
	m_pCurrentScene->Render();
}

void dae::SceneManager::LateUpdate()
{
	if(m_pCurrentScene == nullptr)
		return;
	m_pCurrentScene->LateUpdate();
}

void dae::SceneManager::CleanUp()
{
	for(size_t i = 0; i < m_scenes.size(); ++i)
	{
		m_scenes[i]->CleanUp();
		if(m_scenes[i]->GetDestructionFlag())
		{
			m_scenes.erase(m_scenes.begin() + static_cast<int>(i));
		}
		SceneNavigator::LoadStage();
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

void dae::SceneManager::RemoveScene(const std::string& name) const
{
	for(size_t i = 0; i < m_scenes.size(); ++i)
	{
		if(m_scenes[i]->GetSceneName() == name)
			m_scenes[i]->DestroyScene();
	}
}

void dae::SceneManager::FixedUpdate()
{
	if(m_pCurrentScene == nullptr)
		return;
	m_pCurrentScene->FixedUpdate();
}
