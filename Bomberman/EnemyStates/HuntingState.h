#pragma once
#include "BaseState.h"


namespace dae
{
	class GridComponent;

	class HuntingState final : public dae::BaseState {
	public:
		HuntingState(GameObject* pPlayer, GridComponent* pGrid, GameObject* pParent);
		HuntingState(const HuntingState& other) = delete;
		HuntingState(HuntingState&& other) noexcept = delete;
		HuntingState& operator=(const HuntingState& other) = delete;
		HuntingState& operator=(HuntingState&& other) noexcept = delete;
		~HuntingState() override = default;

		void      Update() override;
		void      OnEnter() override;

	private:
		void           DetermineWalkDirection(const glm::vec2& playerPos);
		GridComponent* m_pGridComp{nullptr};
		GameObject*    m_pPlayer{nullptr};
	};
}
