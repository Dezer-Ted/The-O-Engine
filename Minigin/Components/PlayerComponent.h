#pragma once
#include "BaseComponent.h"
#include "../Observable.h"

namespace dae
{
	class PlayerComponent final : public dae::BaseComponent, public dae::Observable {
	public:
		PlayerComponent(GameObject* pParent);
		PlayerComponent(const PlayerComponent&) = delete;
		PlayerComponent(PlayerComponent&&) = delete;
		PlayerComponent& operator=(const PlayerComponent&) = delete;
		PlayerComponent& operator=(PlayerComponent&&) = delete;
		~PlayerComponent() override = default;
		void AddObserver(Observer* pObserver) override;
		void AddHP(int amount);
		int  GetHP() const;
		int GetScore() const;
		void AddScore(int value);
	private:
		int m_MaxHp{3};
		int m_CurrentHp{m_MaxHp};
		int m_Score{0};
	};
}
