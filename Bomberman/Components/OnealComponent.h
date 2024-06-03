#pragma once
#include "Components/BaseComponent.h"
#include "Engine/DesignPatterns/Observer.h"
#include "../EnemyStates/RandomMovementState.h"
#include "../EnemyStates/HuntingState.h"
#include "Engine/DesignPatterns/Observable.h"


namespace dae
{
	class BaseState;
	class ObserverEventData;
	class MovementComponent;

	class GridComponent;

	class SightedEventData final : public ObserverEventData {
	public:
		SightedEventData(BaseComponent* component, const glm::vec2& playerGridPos, GridComponent* pGrid, const glm::vec2& enemyPos);
		SightedEventData(const SightedEventData& other) = delete;
		SightedEventData(SightedEventData&& other) noexcept = delete;
		SightedEventData& operator=(const SightedEventData& other) = delete;
		SightedEventData& operator=(SightedEventData&& other) noexcept = delete;
		~SightedEventData() override = default;
		glm::vec2      m_Playerpos{};
		GridComponent* m_pGrid{nullptr};
		glm::vec2      m_EnemyPos{};
	};

	//TODO: Unhappy with the implementation but works for now Fix when turning corners works correctly
	class OnealComponent final : public dae::BaseComponent, public Observer, public Observable {
	public:
		OnealComponent(GameObject* pParent);
		OnealComponent(const OnealComponent& other) = delete;
		OnealComponent(OnealComponent&& other) noexcept = delete;
		OnealComponent& operator=(const OnealComponent& other) = delete;
		OnealComponent& operator=(OnealComponent&& other) noexcept = delete;
		~OnealComponent() override;
		void Notify(Utils::GameEvent event, ObserverEventData* eventData) override;
		void Update() override;
		void Initialize(GridComponent* pGrid, GameObject* pPlayer);

	private:
		void                                 IsPlayerInSight();
		const float                          m_DirectionChangeCooldown{1.f};
		float                                m_CurrentCooldown{0.f};
		const float                          m_HuntingDuration{5.f};
		float                                m_CurrentHuntLength{0.f};
		MovementComponent*                   m_pMoveComp{nullptr};
		GridComponent*                       m_pGridComp{nullptr};
		GameObject*                          m_pPlayer{nullptr};
		std::unique_ptr<RandomMovementState> m_pRandomMovementState{std::make_unique<RandomMovementState>()};
		std::unique_ptr<dae::HuntingState>   m_pHuntingState{std::make_unique<HuntingState>()};
		BaseState*                           m_pCurrentState{nullptr};
		glm::vec2                            m_WalkDirection{};
	};
}
