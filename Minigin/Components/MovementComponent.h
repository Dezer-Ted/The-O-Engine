#pragma once

#include "../Engine/DesignPatterns/Observable.h"
#include "BaseComponent.h"
#include "../SceneObjects/GameObject.h"

namespace dae
{
	class MovementComponent final : public BaseComponent, public Observable {
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
		void              UndoMovement();
		void              Update() override;

	private:
		MovementDirection DetermineDirection(const glm::vec2& input);

		float             m_MovementSpeed{50};
		glm::vec2         m_LastDirection{};
		MovementDirection m_Direction{};
		glm::vec3         m_LastPosition{};
	};
}
