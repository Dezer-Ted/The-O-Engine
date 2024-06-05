#pragma once
#include "Engine/DesignPatterns/Observable.h"

namespace dae
{
	class DirectionChangeEvent final : public ObserverEventData {
	public:
		DirectionChangeEvent(BaseComponent* component, const glm::vec2& direction);
		DirectionChangeEvent(const DirectionChangeEvent& other) = delete;
		DirectionChangeEvent(DirectionChangeEvent&& other) noexcept = delete;
		DirectionChangeEvent& operator=(const DirectionChangeEvent& other) = delete;
		DirectionChangeEvent& operator=(DirectionChangeEvent&& other) noexcept = delete;
		~DirectionChangeEvent() override = default;
		glm::vec2 m_Direction{};
	};

	class BaseState : public Observable {
	public:
		BaseState(GameObject* pParent) { m_pParent = pParent; }
		BaseState(const BaseState& other) = delete;
		BaseState(BaseState&& other) noexcept = delete;
		BaseState& operator=(const BaseState& other) = delete;
		BaseState& operator=(BaseState&& other) noexcept = delete;
		~BaseState() override = default;

		virtual void Update() = 0;

		virtual glm::vec2 GetDirection() { return m_Direction; }

		virtual void OnEnter()
		{
		}

		virtual void OnExit()
		{
		}

	protected:
		glm::vec2 GenerateRandomDirection();

		GameObject* GetParent() const { return m_pParent; }
		glm::vec2   m_Direction{GenerateRandomDirection()};

	private:
		GameObject* m_pParent{nullptr};
	};
}
