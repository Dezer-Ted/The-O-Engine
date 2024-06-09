#pragma once
#include "BaseState.h"
#include "Engine/DesignPatterns/Observer.h"


namespace dae
{
	class GridComponent;

	class HuntingState final : public dae::BaseState, public Observer {
	public:
		HuntingState(GridComponent* pGrid, GameObject* pParent);
		HuntingState(const HuntingState& other) = delete;
		HuntingState(HuntingState&& other) noexcept = delete;
		HuntingState& operator=(const HuntingState& other) = delete;
		HuntingState& operator=(HuntingState&& other) noexcept = delete;
		~HuntingState() override = default;

		void Update() override;
		void OnEnter() override;

	private:
		void           DetermineWalkDirection(const glm::vec2& playerPos);

	public:
		void Notify(Utils::GameEvent event, ObserverEventData* eventData) override;

	private:
		GridComponent* m_pGridComp{nullptr};
		GameObject*    m_pPlayer{nullptr};
	};
}
