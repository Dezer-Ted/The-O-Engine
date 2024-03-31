#pragma once
#include "Engine/DesignPatterns/Observable.h"
#include "Engine/DesignPatterns/Observer.h"
#include "Components/BaseComponent.h"
#include "Components/MovementComponent.h"

namespace dae
{
	class SpriteComponent;

	class PlayerComponent final : public BaseComponent, public Observer {
	public:
		PlayerComponent(GameObject* pParent);
		PlayerComponent(const PlayerComponent&) = delete;
		PlayerComponent(PlayerComponent&&) = delete;
		PlayerComponent& operator=(const PlayerComponent&) = delete;
		PlayerComponent& operator=(PlayerComponent&&) = delete;
		~PlayerComponent() override = default;
		void Notify(Utils::GameEvent event, BaseComponent* components, std::unique_ptr<Blackboard> pBlackboard) override;

	private:
		void ChangeAnimation(MovementComponent::MovementDirection direction);

		MovementComponent* m_pMoveComp {nullptr};
		SpriteComponent* m_pSpriteComponent {nullptr};
	};
}
