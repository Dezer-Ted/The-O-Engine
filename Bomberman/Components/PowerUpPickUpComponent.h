#pragma once
#include "PowerUpComponent.h"
#include "Components/BaseComponent.h"

namespace dae
{
	class PowerUpPickUpComponent final : public dae::BaseComponent, public Observer {
	public:
		PowerUpPickUpComponent(GameObject* pParent);
		PowerUpPickUpComponent(const PowerUpPickUpComponent& other) = delete;
		PowerUpPickUpComponent(PowerUpPickUpComponent&& other) noexcept = delete;
		PowerUpPickUpComponent& operator=(const PowerUpPickUpComponent& other) = delete;
		PowerUpPickUpComponent& operator=(PowerUpPickUpComponent&& other) noexcept = delete;
		~PowerUpPickUpComponent() override = default;
		void     SetPowerUp(PowerUps powerUp);
		PowerUps GetPowerUp() const;
		void     Notify(Utils::GameEvent event, ObserverEventData* eventData) override;

	private:
		PowerUps m_PowerUps{PowerUps::FireUp};
	};
}
