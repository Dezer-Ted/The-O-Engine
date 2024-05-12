#pragma once
#include "Engine/DesignPatterns/Observable.h"
#include "Engine/DesignPatterns/Observer.h"
#include "Components/BaseComponent.h"
#include "../Components/MovementComponent.h"

namespace dae
{
	class GridComponent;
	class SpriteComponent;

	class PlayerComponent final : public BaseComponent, public Observer {
	public:
		PlayerComponent(GameObject* pParent);
		PlayerComponent(const PlayerComponent&) = delete;
		PlayerComponent(PlayerComponent&&) = delete;
		PlayerComponent& operator=(const PlayerComponent&) = delete;
		PlayerComponent& operator=(PlayerComponent&&) = delete;
		~PlayerComponent() override = default;
		void Notify(Utils::GameEvent event, ObserverEventData* eventData) override;
		void DropBomb();
		void SetGrid(GridComponent* pGrid);

	private:
		void               ChangeAnimation(MovementComponent::MovementDirection direction);
		GridComponent*              m_pGrid{nullptr};
		MovementComponent* m_pMoveComp{nullptr};
		SpriteComponent*   m_pSpriteComponent{nullptr};
	};
}
