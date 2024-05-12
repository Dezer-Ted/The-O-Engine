#pragma once
#include "BaseState.h"
#include "Engine/DesignPatterns/Observer.h"

namespace dae
{
	class HuntingState final : public dae::BaseState, public dae::Observer {
	public:
		HuntingState() = default;
		HuntingState(const HuntingState& other) = delete;
		HuntingState(HuntingState&& other) noexcept = delete;
		HuntingState& operator=(const HuntingState& other) = delete;
		HuntingState& operator=(HuntingState&& other) noexcept = delete;

		void      HandleWallCollision() override;
		bool      Update() override;
		glm::vec2 GetMovementDirection() override;
		~HuntingState() override;
		void Notify(Utils::GameEvent event, dae::ObserverEventData* eventData) override;

	private:
		void      SetDirection(const glm::vec2 direction);
		void DetermineDirection();
		glm::vec2 m_LastSeenPos{};
		glm::vec2 m_Direction{};
		bool      m_DirtyFlag{false};
	};
}
