#pragma once
#include <vector>

#include "BaseState.h"

namespace dae
{
	class RandomMovementState final : public BaseState {
	public:
		RandomMovementState() = default;
		RandomMovementState(const RandomMovementState& other) = delete;
		RandomMovementState(RandomMovementState&& other) noexcept = delete;
		RandomMovementState& operator=(const RandomMovementState& other) = delete;
		RandomMovementState& operator=(RandomMovementState&& other) noexcept = delete;
		~RandomMovementState() override;

		void      HandleWallCollision() override;
		bool      Update() override;
		glm::vec2 GetMovementDirection() override;

	private:
		glm::vec2 GenerateRandomDirection() const;
		void      SetMovementDirection(const glm::vec2& input);

		bool                   m_DirtyFlag{false};
		glm::vec2              m_MovementDirection{};
		std::vector<glm::vec2> m_Directions{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
		
	};
}
