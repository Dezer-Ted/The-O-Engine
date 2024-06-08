#pragma once
#include "Engine/DesignPatterns/Observer.h"
#include "Engine/DesignPatterns/Singleton.h"

namespace dae
{
	class ScoreComponent;
	class EnemyComponent;

	class EnemyTracker final : public dae::Singleton<EnemyTracker>, public dae::Observer {
	public:
		EnemyTracker(const EnemyTracker& other) = delete;
		EnemyTracker(EnemyTracker&& other) noexcept = delete;
		EnemyTracker& operator=(const EnemyTracker& other) = delete;
		EnemyTracker& operator=(EnemyTracker&& other) noexcept = delete;
		~EnemyTracker() override = default;
		void RegisterEnemy(dae::EnemyComponent* pEnemyComp);
		void Notify(Utils::GameEvent event, dae::ObserverEventData* eventData) override;
		bool NoEnemiesLeft() const;
		void RegisterScoreComp(ScoreComponent* pScoreComp);
		void ResetEnemies();
	private:
		void UnregisterEnemy(EnemyComponent* pEnemyComp);
		friend class Singleton<EnemyTracker>;
		EnemyTracker() = default;
		std::vector<EnemyComponent*> m_Enemies;
		ScoreComponent*              m_pScoreComp{nullptr};
	};
}
