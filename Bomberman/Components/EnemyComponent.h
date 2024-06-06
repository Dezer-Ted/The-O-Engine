#pragma once
#include <memory>
#include <vector>

#include "../EnemyStates/BaseState.h"
#include "../EnemyStates/EnemyTransitions/BaseTransition.h"
#include "Components/BaseComponent.h"
#include "Engine/DesignPatterns/Observer.h"


namespace dae
{
	class SpriteComponent;
	class GameObject;
	class MovementComponent;

	enum class EnemyType {
		Balloom,
		Oneal,
		Doll,
		Minvo
	};

	class EnemyDiedEvent final : public ObserverEventData {
	public:
		EnemyDiedEvent(BaseComponent* comp, EnemyType type);
		EnemyDiedEvent(const EnemyDiedEvent& other) = delete;
		EnemyDiedEvent(EnemyDiedEvent&& other) noexcept = delete;
		EnemyDiedEvent& operator=(const EnemyDiedEvent& other) = delete;
		EnemyDiedEvent& operator=(EnemyDiedEvent&& other) noexcept = delete;
		EnemyType       m_Type{EnemyType::Balloom};
		~EnemyDiedEvent() override = default;
	};

	class EnemyComponent final : public dae::BaseComponent, public Observer, public Observable {
	public:
		EnemyComponent(GameObject* pParent);
		EnemyComponent(const EnemyComponent& other) = delete;
		EnemyComponent(EnemyComponent&& other) noexcept = delete;
		EnemyComponent& operator=(const EnemyComponent& other) = delete;
		EnemyComponent& operator=(EnemyComponent&& other) noexcept = delete;
		~EnemyComponent() override = default;

		void            Notify(Utils::GameEvent event, ObserverEventData* eventData) override;
		void            Update() override;
		BaseState*      AddState(std::unique_ptr<BaseState> state);
		BaseTransition* AddTransition(std::unique_ptr<BaseTransition> transition);
		void            SetState(BaseState* pState);
		void            SetEnemyType(EnemyType type);

	private:
		EnemyType                                    m_Type{EnemyType::Balloom};
		MovementComponent*                           m_pMoveComp{nullptr};
		SpriteComponent*                             m_pSpriteComp{nullptr};
		std::vector<std::unique_ptr<BaseState>>      m_States;
		BaseState*                                   m_pCurrentState{nullptr};
		std::vector<std::unique_ptr<BaseTransition>> m_Transitions;
		std::vector<BaseTransition*>                 m_ActiveTransitions;
		glm::vec2                                    m_Direction{};
		bool                                         m_IsDying{false};
		void                                         SetActiveTransitions();
	};
}
