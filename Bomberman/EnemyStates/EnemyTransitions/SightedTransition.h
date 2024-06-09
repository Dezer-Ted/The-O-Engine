#pragma once
#include "BaseTransition.h"


namespace dae
{
	class GridComponent;

	enum class Alignment {
		Horizontal,
		Vertical
	};

	class PlayerSightedEventData final : public ObserverEventData {
	public:
		PlayerSightedEventData(GameObject* pPlayer);
		PlayerSightedEventData(const PlayerSightedEventData& other) = delete;
		PlayerSightedEventData(PlayerSightedEventData&& other) noexcept = delete;
		PlayerSightedEventData& operator=(const PlayerSightedEventData& other) = delete;
		PlayerSightedEventData& operator=(PlayerSightedEventData&& other) noexcept = delete;

		GameObject* m_pPlayer{nullptr};
		~PlayerSightedEventData() override = default;
	};

	class SightedTransition final : public dae::BaseTransition {
	public:
		SightedTransition(BaseState* pFromState, BaseState* pToState, const std::vector<GameObject*>& players, GameObject* pParent, GridComponent* pGrid,
		                  bool       invertCondition);
		SightedTransition(const SightedTransition& other) = delete;
		SightedTransition(SightedTransition&& other) noexcept = delete;
		SightedTransition& operator=(const SightedTransition& other) = delete;
		SightedTransition& operator=(SightedTransition&& other) noexcept = delete;
		~SightedTransition() override = default;

		void CheckExitCondition() override;

	private:
		void DetectPlayerAlignment(GameObject* pPlayer);
		void DetermineDirection(Alignment alignment, int start, int end, int alignedLine, GameObject* pPlayer);
		bool CheckIfObscured(Alignment alignment, int alignedLine, int offset, int start, bool isPositiv);

		std::vector<GameObject*> m_Players;
		GameObject*              m_pParent{nullptr};
		GridComponent*           m_pGrid{nullptr};
		bool                     m_ConditionInverted{false};
	};
}
