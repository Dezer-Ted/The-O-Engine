#include "EncircleComponent.h"
#include "../SceneObjects/GameObject.h"
#include "../Engine/DesignPatterns/Singleton.h"
#include "../Engine/DeltaTime.h"
#include "../Engine/Utils/Utils.h"

dae::EncircleComponent::EncircleComponent(GameObject* pParent): BaseComponent(pParent)
{
	SetPivot(GetParent()->GetTransform().GetWorldPosition());
	m_CurrentRotationDEG = static_cast<float>(rand() % 360);
}

void dae::EncircleComponent::Update()
{
	if(GetParent()->GetParent() != nullptr) SetPivot(GetParent()->GetParent()->GetTransform().GetWorldPosition());
	m_CurrentRotationDEG += m_DegreesPerSecond * Singleton<DeltaTime>::GetInstance().GetDeltaTime();
	if(m_CurrentRotationDEG > 360.f) m_CurrentRotationDEG = 0.f;
	const float rotationRad{Utils::DegToRad(m_CurrentRotationDEG)};
	glm::vec3   offset{
		cos(rotationRad) * m_Radius,
		sin(rotationRad) * m_Radius,
		0.f
	};
	if(GetParent()->GetParent() == nullptr) offset += m_Pivot;
	GetParent()->GetTransform().SetLocalPosition(offset);
}

void dae::EncircleComponent::SetPivot(const glm::vec3& pivot)
{
	m_Pivot = pivot;
}

void dae::EncircleComponent::SetRadius(float radius)
{
	m_Radius = radius;
}
