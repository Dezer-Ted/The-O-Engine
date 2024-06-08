#pragma once
#include <unordered_map>

#include "EnemyComponent.h"
#include "Components/BaseComponent.h"
#include "Engine/DesignPatterns/Observer.h"


namespace dae
{
	class TextComponent;

	class ScoreComponent final : public dae::BaseComponent, public Observer {
	public:
		ScoreComponent(GameObject* pParent);
		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) noexcept = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) noexcept = delete;

		void Notify(Utils::GameEvent event, ObserverEventData* eventData) override;
		~ScoreComponent() override;

	private:
		int                                m_Score{0};
		std::unordered_map<EnemyType, int> m_ScoreMap;
		TextComponent*                     m_pTextComp{nullptr};
	};
}
