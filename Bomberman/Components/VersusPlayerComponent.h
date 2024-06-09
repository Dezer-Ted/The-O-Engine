#pragma once
#include "Components/BaseComponent.h"
#include "Engine/DesignPatterns/Observable.h"
#include "Engine/DesignPatterns/Observer.h"


namespace dae
{
	class MovementComponent;
	class SpriteComponent;

	class VersusPlayerComponent final : public dae::BaseComponent, public Observer , public Observable{
	public:
		VersusPlayerComponent(GameObject* pParent);
		VersusPlayerComponent(const VersusPlayerComponent& other) = delete;
		VersusPlayerComponent(VersusPlayerComponent&& other) noexcept = delete;
		VersusPlayerComponent& operator=(const VersusPlayerComponent& other) = delete;
		VersusPlayerComponent& operator=(VersusPlayerComponent&& other) noexcept = delete;
		~VersusPlayerComponent() override = default;
		void Notify(Utils::GameEvent event, ObserverEventData* eventData) override;

	private:
		SpriteComponent*   m_pSpriteComp{nullptr};
		MovementComponent* m_pMoveComp{nullptr};
		bool               m_IsDead{false};
	};
}
