#pragma once

#include <SDL_rect.h>

#include "Engine/DesignPatterns/Observable.h"
#include "Components/BaseComponent.h"
#include "Engine/DesignPatterns/Observer.h"
#include "SceneObjects/GameObject.h"

namespace dae
{
	class MovementComponent final : public BaseComponent, public Observable, public Observer {
	public:
		enum class MovementDirection {
			Up,
			Down,
			Left,
			Right
		};

		MovementComponent(GameObject* pParent);
		MovementComponent(const MovementComponent&) = delete;
		MovementComponent(MovementComponent&&) = delete;
		MovementComponent& operator=(const MovementComponent&) = delete;
		MovementComponent& operator=(MovementComponent&&) = delete;
		~MovementComponent() override = default;
		void              ApplyMovement(const glm::vec2& input);
		MovementDirection GetDirection() const;
		void              UndoMovement() const;
		void              Update() override;
		void              SetSpeed(float movementSpeed);
		void              Notify(Utils::GameEvent event, ObserverEventData* eventData) override;

	private:
		MovementDirection DetermineDirection(const glm::vec2& input);
		void              DodgeWalls(const glm::vec2& input);
		void              DodgeYCheck(const SDL_Rect& bounds,const glm::vec2& playerCenter,float bufferRange);
		void              DodgeXCheck(const SDL_Rect& bounds,const glm::vec2& playerCenter,float bufferRange);
		void              HandleCollision(dae::ObserverEventData* eventData);
		float             m_MovementSpeed{100.f};
		glm::vec2         m_LastDirection{};
		MovementDirection m_Direction{};
		glm::vec3         m_LastPosition{};
		bool              m_IsDodging{};
		glm::vec2         m_DodgeDirection{};
	};
}
