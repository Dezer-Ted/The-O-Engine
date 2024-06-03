#pragma once
#include "Components/BaseComponent.h"
#include "Engine/DesignPatterns/Observer.h"

namespace dae
{
	class SpriteComponent;
	class WallComponent : public BaseComponent, public Observer {
	public:
		WallComponent(GameObject* pOwner);
		WallComponent(const WallComponent& other) = delete;
		WallComponent(WallComponent&& other) noexcept = delete;
		WallComponent& operator=(const WallComponent& other) = delete;
		WallComponent& operator=(WallComponent&& other) noexcept = delete;
		~WallComponent() override = default;

		void StartDestruction();
		void Notify(Utils::GameEvent event, ObserverEventData* eventData) override;
		

	private:
		SpriteComponent* m_pSpriteComponent;
		bool m_IsDestroyed = true;
	};
}
