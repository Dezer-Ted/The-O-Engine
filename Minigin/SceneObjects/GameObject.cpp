#include "GameObject.h"

#include "../Engine/DesignPatterns/Singleton.h"
#include "Time.h"
#include "Scene.h"
dae::GameObject::~GameObject() = default;

dae::Transform& dae::GameObject::GetTransform()
{
	return m_Transform;
}

void dae::GameObject::Update()
{
	for(const auto& component : m_ComponentList)
	{
		component->Update();
	}
}

void dae::GameObject::Render() const
{
	for(const auto& component : m_ComponentList)
	{
		component->Render();
	}
}

void dae::GameObject::LateUpdate()
{
	for(const auto& component : m_ComponentList)
	{
		component->LateUpdate();
	}
}

void dae::GameObject::DestroyComponents()
{
	for(unsigned int index = 0; index < m_ComponentList.size(); ++index)
	{
		if(m_ComponentList[index]->m_DestructionFlag)
		{
			m_ComponentList.erase(m_ComponentList.begin() + index);
		}
	}
}

bool dae::GameObject::GetDestructionFlag() const
{
	return m_DestructionFlag;
}

void dae::GameObject::DestroyObject()
{
	m_DestructionFlag = true;
	for(auto child : m_Children)
	{
		child->DestroyObject();
	}
}

dae::Scene* dae::GameObject::GetParentScene()
{
	return m_pParentScene;
}

dae::GameObject* dae::GameObject::GetParent() const
{
	return m_Parent;
}

void dae::GameObject::SetParent(GameObject* pParent, bool keepWorldPosition)
{
	if(pParent == m_Parent)
		return;
	for(const auto& child : m_Children)
	{
		if(child == pParent)
			return;
	}
	if(pParent != nullptr)
	{
		for(unsigned int index = 0; index < m_Children.size(); ++index)
		{
			if(m_Parent->m_Children[index] == this)
				m_Parent->m_Children.erase(m_Parent->m_Children.begin() + index);
		}
		m_Parent = pParent;
		m_Parent->m_Children.push_back(this);

		if(keepWorldPosition)
			m_Transform.SetLocalPosition(m_Transform.GetLocalPosition() - m_Parent->GetTransform().GetWorldPosition());

	}
	else
	{
		if(keepWorldPosition)
			m_Transform.SetLocalPosition(m_Transform.GetWorldPosition());

		m_Parent = pParent;

	}

}

const std::vector<dae::GameObject*>& dae::GameObject::GetChildren()
{
	return m_Children;
}

void dae::GameObject::Translate(const glm::vec2& input)
{
	m_Transform.SetLocalPosition(glm::vec3{input.x, input.y, 0} + m_Transform.GetLocalPosition());
}

void dae::GameObject::FixedUpdate()
{
	for(const auto& component : m_ComponentList)
	{
		component->FixedUpdate();
	}
}

void dae::GameObject::SetTag(const std::string& tag)
{
	m_Tag = tag;
}

std::string dae::GameObject::GetTag() const
{
	return m_Tag;
}

std::string dae::GameObject::GetLayer() const
{
	return m_Layer;
}

void dae::GameObject::SetLayer(const std::string& layer) 
{
	m_Layer = layer;
}


void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetLocalPosition(x, y, 0.0f);
}

dae::GameObject::GameObject(Scene* pParentScene): m_Transform{this}
                                                  , m_pParentScene(pParentScene)
{
}
