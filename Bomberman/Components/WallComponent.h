#pragma once
#include "PowerUpComponent.h"
#include "Components/BaseComponent.h"
#include "Engine/DesignPatterns/Observer.h"

namespace dae
{
	class SpriteComponent;

	class WallComponent final : public BaseComponent, public Observer {
	public:
		WallComponent(GameObject* pOwner);
		WallComponent(const WallComponent& other) = delete;
		WallComponent(WallComponent&& other) noexcept = delete;
		WallComponent& operator=(const WallComponent& other) = delete;
		WallComponent& operator=(WallComponent&& other) noexcept = delete;
		~WallComponent() override = default;

		void StartDestruction();
		void Notify(Utils::GameEvent event, ObserverEventData* eventData) override;
		void SetPowerUp(PowerUps powerUp);
		void SetExit();
		bool HasPowerUp() const;

	private:
		void DropExit();
		void             DropItem() const;
		SpriteComponent* m_pSpriteComponent;
		bool             m_IsDestroyed{false};
		bool             m_HoldsItem{false};
		bool             m_HoldsExit{false};
		PowerUps         m_PowerUp{PowerUps::FireUp};
	};
}
