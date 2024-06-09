#include "CameraComponent.h"

#include "../Rendering/Renderer.h"
#include "../SceneObjects/GameObject.h"

dae::CameraComponent::CameraComponent(GameObject* pParent) : BaseComponent(pParent)
{
	m_StartPosition = GetParent()->GetTransform().GetWorldPosition();
	Renderer::GetInstance().SetCamera(this);
}

glm::vec2 dae::CameraComponent::GetOffSet() const
{
	return m_CurrentOffset;
}


void dae::CameraComponent::CheckInBoundsX(glm::vec2& pos2D) const
{
	if(m_Bounds.x > pos2D.x - static_cast<float>(m_CameraSize.w) / 2)
		pos2D.x = static_cast<float>(m_CameraSize.w) / 2.f;
	else if(m_Bounds.x + m_Bounds.w < pos2D.x + static_cast<float>(m_CameraSize.w) / 2)
		pos2D.x = m_Bounds.x + m_Bounds.w - static_cast<float>(m_CameraSize.w) / 2;
}

void dae::CameraComponent::CheckInBoundsY(glm::vec2& pos2D) const
{
	if(m_Bounds.y > pos2D.y - static_cast<float>(m_CameraSize.h) / 2)
		pos2D.y = static_cast<float>(m_CameraSize.h) / 2.f;
	else if(m_Bounds.y + m_Bounds.h < pos2D.y + static_cast<float>(m_CameraSize.h) / 2)
		pos2D.y = m_Bounds.y + m_Bounds.h - static_cast<float>(m_CameraSize.h) / 2;
}

void dae::CameraComponent::Update()
{
	const auto currentWorldPosition = GetParent()->GetTransform().GetWorldPosition();

	glm::vec2 pos2D{currentWorldPosition.x, currentWorldPosition.y};
	if(m_AdditionalTarget != nullptr)
	{
		const auto otherWorldPos{m_AdditionalTarget->GetTransform().GetWorldPosition()};
		pos2D = glm::vec2{(otherWorldPos.x + currentWorldPosition.x) / 2, (otherWorldPos.y + currentWorldPosition.y) / 2};
	}

	if(m_LastPosition != pos2D)
	{
		CheckInBoundsX(pos2D);
		CheckInBoundsY(pos2D);
		m_CurrentOffset = pos2D - glm::vec2{static_cast<float>(m_CameraSize.w) / 2.f, static_cast<float>(m_CameraSize.h) / 2.f};
		m_LastPosition = pos2D;
	}
}

void dae::CameraComponent::SetBounds(const SDL_Rect& bounds)
{
	m_Bounds = bounds;
}

void dae::CameraComponent::SetAdditionalTarget(GameObject* pOther)
{
	m_AdditionalTarget = pOther;
}

void dae::CameraComponent::Notify(Utils::GameEvent event, ObserverEventData* )
{
	if(event == Utils::GameEvent::PlayerDied)
	{
		m_AdditionalTarget = nullptr;
	}
}
