#include "BaseComponent.h"

dae::BaseComponent::BaseComponent(GameObject* pParent)
{
	m_Parent = pParent;
}

dae::BaseComponent::~BaseComponent()
{

}

bool dae::BaseComponent::GetDestructionFlag()
{
	return m_DestructionFlag;
}

void dae::BaseComponent::DestroyComponent()
{
	m_DestructionFlag = true;
}

dae::GameObject* dae::BaseComponent::GetParent() const
{
	return m_Parent;
}
