#pragma once
#include "Components/BaseComponent.h"
#include "Engine/DesignPatterns/Observer.h"

namespace dae
{
	class ExitComponent final : public BaseComponent, public Observer {
	public:
		ExitComponent(GameObject* pParent);
		ExitComponent(const ExitComponent& other) = delete;
		ExitComponent(ExitComponent&& other) noexcept = delete;
		ExitComponent& operator=(const ExitComponent& other) = delete;
		ExitComponent& operator=(ExitComponent&& other) noexcept = delete;
		~ExitComponent() override = default;
		void Notify(Utils::GameEvent event, ObserverEventData* eventData) override;

	private:
	};
}
