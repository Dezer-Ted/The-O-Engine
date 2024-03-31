#include "Scene.h"
#include "GameObject.h"

#include <algorithm>

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::shared_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::FixedUpdate()
{
	for(auto& object : m_objects)
	{
		object->FixedUpdate();
	}
}

void Scene::Update()
{
	for(auto& object : m_objects)
	{
		object->Update();
	}
	m_pCollisionCheck->CheckAllColliders();
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

void Scene::LateUpdate()
{
	for (const auto& object : m_objects)
	{
		object->LateUpdate();
	}
}

void Scene::CleanUp()
{
	for (unsigned int index = 0; index < m_objects.size(); ++index)
	{
		if(m_objects[index]->GetDestructionFlag())
		{
			m_objects.erase(m_objects.begin() + index);
		}
		m_objects[index]->DestroyComponents();
	}
}

void Scene::DestroyScene()
{
	m_DestructionFlag = true;
}

void Scene::AddCollider(ColliderComponent* collider) const
{
	m_pCollisionCheck->AddCollider(collider);
}

bool Scene::GetDestructionFlag() const
{
	return m_DestructionFlag;
}



