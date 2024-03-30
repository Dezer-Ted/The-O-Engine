#pragma once
#include "Observable.h"
#include "Observer.h"
#include "Components/BaseComponent.h"
#include "Components/MovementComponent.h"

namespace dae
{
	class SpriteComponent;
	class PlayerComponent final : public BaseComponent, public Observer{
	public:
		PlayerComponent(GameObject* pParent);
		PlayerComponent( const PlayerComponent& ) = delete;
		PlayerComponent(PlayerComponent&&) = delete;
		PlayerComponent& operator=(const PlayerComponent& ) = delete;
		PlayerComponent& operator=(PlayerComponent&& ) = delete;
		~PlayerComponent() override = default;
		void Notify(Utils::GameEvent event, BaseComponent* components) override;

	private:
		void ChangeAnimation(MovementComponent::MovementDirection direction);
		
		SpriteComponent* m_pSpriteComponent;
	};
}
