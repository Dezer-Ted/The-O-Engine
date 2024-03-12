#include "MiscFunctionComponent.h"

dae::MiscFunctionComponent::MiscFunctionComponent(GameObject* pParent): BaseComponent(pParent)
{
}

void dae::MiscFunctionComponent::SetFunction(const std::function<void(GameObject*)>& function)
{
	m_Function = function;
}

void dae::MiscFunctionComponent::Update()
{
	m_Function(GetParent());
}

void dae::MiscFunctionComponent::LateUpdate()
{
}

void dae::MiscFunctionComponent::Render()
{
}
