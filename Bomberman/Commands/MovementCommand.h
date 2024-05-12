#pragma once
#include "Engine/DesignPatterns/Command.h"

namespace dae
{
	class MovementComponent;
    
    	class Move final : public GameObjectCommand {
    	public:
    		void Execute2DAxis(const glm::vec2& input) override;
    		Move(GameObject* gameObject);
    		virtual ~Move() override = default;
    
    	private:
    		MovementComponent* m_pMovementComp{nullptr};
    	};

}
	