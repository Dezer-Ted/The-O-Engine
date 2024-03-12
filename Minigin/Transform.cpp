#include "Transform.h"
#include "GameObject.h"


dae::Transform::Transform(GameObject* pOwner) :
	m_pOwner(pOwner)
{
}

glm::vec3 dae::Transform::GetWorldPosition()
{
	if(m_pOwner == nullptr)
		return {0,0,0};
	if(m_PositionDirty)
		UpdateWorldPosition();
	return m_WorldPosition;
}

void dae::Transform::SetLocalPosition(const float x, const float y, const float z)
{
	m_LocalPosition.x = x;
	m_LocalPosition.y = y;
	m_LocalPosition.z = z;
	m_PositionDirty = true;
}

void dae::Transform::SetLocalPosition(const glm::vec3& pos)
{
	m_LocalPosition = pos;
	m_PositionDirty = true;
}

void dae::Transform::UpdateWorldPosition()
{
	if(m_pOwner->GetParent() == nullptr)
		m_WorldPosition = m_LocalPosition;
	else
		m_WorldPosition = m_pOwner->GetParent()->GetTransform().GetWorldPosition() + m_LocalPosition;
		
	m_PositionDirty = false;
}
