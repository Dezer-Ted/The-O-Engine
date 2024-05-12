#pragma once
#include <glm/vec2.hpp>

namespace dae
{
	class BaseState {
	public:
		virtual void      HandleWallCollision() = 0;
		virtual bool      Update() = 0;
		virtual glm::vec2 GetMovementDirection() = 0;
		virtual           ~BaseState() = default;
	};
}
