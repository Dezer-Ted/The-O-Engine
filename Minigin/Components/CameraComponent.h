#pragma once
#include <SDL_rect.h>
#include <glm/glm.hpp>

#include "BaseComponent.h"
#include "../Engine/DesignPatterns/Observer.h"

namespace dae
{
	class CameraComponent final : public dae::BaseComponent, public Observer {
	public:
		CameraComponent(GameObject* pParent);
		CameraComponent(const CameraComponent&) = delete;
		CameraComponent(CameraComponent&&) = delete;
		CameraComponent& operator=(const CameraComponent&) = delete;
		CameraComponent& operator=(CameraComponent&&) = delete;
		~CameraComponent() override = default;
		glm::vec2 GetOffSet() const;
		void      Update() override;
		void      SetBounds(const SDL_Rect& bounds);
		void      SetAdditionalTarget(GameObject* pOther);

		void Notify(Utils::GameEvent event, ObserverEventData* eventData) override;

	private:
		void CheckInBoundsX(glm::vec2& pos2D) const;
		void CheckInBoundsY(glm::vec2& pos2D) const;

		GameObject*    m_AdditionalTarget{nullptr};
		glm::vec2      m_StartPosition{0, 0};
		glm::vec2      m_CurrentOffset{0, 0};
		glm::vec2      m_LastPosition{0, 0};
		SDL_Rect       m_Bounds{0, 0, 640, 480};
		const SDL_Rect m_CameraSize{0, 0, 640, 480};
	};
}
