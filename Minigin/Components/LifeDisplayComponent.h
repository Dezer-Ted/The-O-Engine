#pragma once
#include "BaseComponent.h"
#include "PlayerComponent.h"
#include "../Observer.h"


namespace dae
{
	class TextComponent;

	class LifeDisplayComponent final : public BaseComponent, public Observer {
	public:
		LifeDisplayComponent(GameObject* pParent);
		LifeDisplayComponent(const LifeDisplayComponent&) = delete;
		LifeDisplayComponent(LifeDisplayComponent&&) = delete;
		LifeDisplayComponent& operator=(const LifeDisplayComponent&) = delete;
		LifeDisplayComponent& operator=(LifeDisplayComponent&&) = delete;
		~LifeDisplayComponent() override = default;
		void Notify(Utils::GameEvent event, BaseComponent* components) override;

	private:
		void           UpdateText(const PlayerComponent* component) const;
		TextComponent* m_pTextComp{nullptr};
		std::string    m_BaseText{"# lives: "};
	};
}
