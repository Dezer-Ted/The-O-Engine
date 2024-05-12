#pragma once
#include "Components/BaseComponent.h"
#include "Engine/ObserverEventData.h"
#include "Engine/DesignPatterns/Observer.h"
namespace dae
{

	class ExplosionComponent final : public BaseComponent, public Observer {
	public:
		void Notify(Utils::GameEvent event, ObserverEventData* eventData) override;

		ExplosionComponent(GameObject* pParent);
		ExplosionComponent(const ExplosionComponent& other) = delete;
		ExplosionComponent(ExplosionComponent&& other) noexcept = delete;
		ExplosionComponent& operator=(const ExplosionComponent& other) = delete;
		ExplosionComponent& operator=(ExplosionComponent&& other) noexcept = delete;
		~ExplosionComponent() override = default;

	private:
	};
}
