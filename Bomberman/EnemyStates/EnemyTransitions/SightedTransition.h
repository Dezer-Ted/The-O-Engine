#pragma once
#include "BaseTransition.h"


namespace dae
{
	class GridComponent;

	enum class Alignment {
		Horizontal,
		Vertical
	};

	class SightedTransition final : public dae::BaseTransition {
	public:
		SightedTransition(BaseState* pFromState, BaseState* pToState, GameObject* pPlayer, GameObject* pParent, GridComponent* pGrid,
		                  bool       invertCondition);
		SightedTransition(const SightedTransition& other) = delete;
		SightedTransition(SightedTransition&& other) noexcept = delete;
		SightedTransition& operator=(const SightedTransition& other) = delete;
		SightedTransition& operator=(SightedTransition&& other) noexcept = delete;
		~SightedTransition() override = default;

		void CheckExitCondition() override;

	private:
		void DetectPlayerAlignment();
		void DetermineDirection(Alignment alignment, int start, int end, int alignedLine);
		bool CheckIfObscured(Alignment alignment, int alignedLine, int offset, int start, bool isPositiv);

		GameObject*    m_pPlayer{nullptr};
		GameObject*    m_pParent{nullptr};
		GridComponent* m_pGrid{nullptr};
		bool           m_ConditionInverted{false};
	};
}
