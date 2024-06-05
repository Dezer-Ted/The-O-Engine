#pragma once
#include "BaseTransition.h"

namespace dae
{
	class CooldownTransition final : public dae::BaseTransition {
	public:
		CooldownTransition(BaseState* pFromState, BaseState* pToState, float cooldown = 0.5f);
		CooldownTransition(const CooldownTransition& other) = delete;
		CooldownTransition(CooldownTransition&& other) noexcept = delete;
		CooldownTransition& operator=(const CooldownTransition& other) = delete;
		CooldownTransition& operator=(CooldownTransition&& other) noexcept = delete;
		~CooldownTransition() override = default;

		void CheckExitCondition() override;
		void ResetTransition() override;

	private:
		float m_Cooldown{0.f};
		float m_CurrentCooldown{0.f};
	};
}
