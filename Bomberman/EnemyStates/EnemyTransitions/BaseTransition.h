#pragma once
#include "../BaseState.h"
#include "Engine/ObserverEventData.h"
#include "Engine/DesignPatterns/Observable.h"


namespace dae
{
	class BaseState;

	class StateTransitionEvent final : public ObserverEventData {
	public:
		StateTransitionEvent(BaseComponent* component, BaseState* toState);
		StateTransitionEvent(const StateTransitionEvent& other) = delete;
		StateTransitionEvent(StateTransitionEvent&& other) noexcept = delete;
		StateTransitionEvent& operator=(const StateTransitionEvent& other) = delete;
		StateTransitionEvent& operator=(StateTransitionEvent&& other) noexcept = delete;
		~StateTransitionEvent() override = default;
		BaseState* m_ToState{nullptr};
	};


	class BaseTransition : public Observable {
	public:
		BaseTransition(BaseState* pFromState, BaseState* pToState);
		BaseTransition(const BaseTransition& other) = delete;
		BaseTransition(BaseTransition&& other) noexcept = delete;
		BaseTransition& operator=(const BaseTransition& other) = delete;
		BaseTransition& operator=(BaseTransition&& other) noexcept = delete;
		~BaseTransition() override = default;

		virtual void CheckExitCondition() = 0;

		virtual void ResetTransition()
		{
		}
		BaseState* GetToState() const { return m_pToState; }
		BaseState* GetFromState() const { return m_pFromState; }

	private:
		BaseState* m_pFromState{nullptr};
		BaseState* m_pToState{nullptr};
	};
}
