#pragma once
#include "Components/BaseComponent.h"
#include "Engine/DesignPatterns/Observer.h"

namespace dae
{
	enum class PowerUps {
		BombUp,
		FireUp,
		Detonator
	};

	class PowerUpComponent final : public dae::BaseComponent, public Observer {
	public:
		PowerUpComponent(GameObject* pOwner);
		PowerUpComponent(const PowerUpComponent& other) = delete;
		PowerUpComponent(PowerUpComponent&& other) noexcept = delete;
		PowerUpComponent& operator=(const PowerUpComponent& other) = delete;
		PowerUpComponent& operator=(PowerUpComponent&& other) noexcept = delete;
		virtual           ~PowerUpComponent() override;

		int  GetBombUpgrade() const;
		int  GetFireUpgrade() const;
		bool GetDetonatorUpgrade() const;
		void Notify(Utils::GameEvent event, ObserverEventData* eventData) override;

	private:
		void ProcessUpgrade(PowerUps powerUp);
		bool m_HasDetonator{false};
		int  m_BombUpgrade{0};
		int  m_FireUpgrade{0};
	};
}
