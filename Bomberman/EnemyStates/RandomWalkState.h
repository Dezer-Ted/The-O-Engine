#pragma once
#include "BaseState.h"
#include "Engine/DesignPatterns/Observer.h"
#include "Engine/ObserverEventData.h"

namespace dae
{
	class RandomWalkState final : public BaseState, public Observer {
	public:
		RandomWalkState(GameObject* pParent);
		RandomWalkState(const RandomWalkState& other) = delete;
		RandomWalkState(RandomWalkState&& other) noexcept = delete;
		RandomWalkState& operator=(const RandomWalkState& other) = delete;
		RandomWalkState& operator=(RandomWalkState&& other) noexcept = delete;
		~RandomWalkState() override = default;

		void Update() override;
		void GenerateUnusedDirection();
		void Notify(Utils::GameEvent event, ObserverEventData* eventData) override;
		void OnEnter() override;

	private:
		const float m_TurnCooldown{0.1f};
		bool        m_HasTurned{false};
		float       m_CurrentCooldown{0.f};
	};
}
