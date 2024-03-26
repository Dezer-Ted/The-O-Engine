#pragma once
#include "BaseComponent.h"
#include "../Observer.h"

namespace dae
{
	class TextComponent;
	class PlayerComponent;

	class ScoreDisplayComponent final : public BaseComponent, public Observer {
	public:
		ScoreDisplayComponent(GameObject* pParent);
		ScoreDisplayComponent(const ScoreDisplayComponent&) = delete;
		ScoreDisplayComponent(ScoreDisplayComponent&&) = delete;
		ScoreDisplayComponent& operator=(const ScoreDisplayComponent&) = delete;
		ScoreDisplayComponent& operator=(ScoreDisplayComponent&&) = delete;
		~ScoreDisplayComponent() override = default;
		void Notify(Utils::GameEvent event, BaseComponent* components) override;

	private:
		void           UpdateText(const PlayerComponent* component) const;
		TextComponent* m_pTextComp{nullptr};
		std::string    m_BaseString{"Score: "};
	};
}
