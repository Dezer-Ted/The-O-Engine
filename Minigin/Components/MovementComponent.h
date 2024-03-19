#pragma once
#include "BaseComponent.h"
#include "../GameObject.h"

namespace dae
{
	class MovementComponent : public dae::BaseComponent {
	public:
		MovementComponent(GameObject* pParent);
		MovementComponent(const MovementComponent&) = delete;
		MovementComponent(MovementComponent&&) = delete;
		MovementComponent& operator=(const MovementComponent&) = delete;
		MovementComponent& operator=(MovementComponent&&) = delete;
		~MovementComponent() = default;
		void ApplyMovement(const glm::vec2& direction);

	private:
		float m_MovementSpeed{50};
	};
}
