#include "EnemyTracker.h"

#include "Components/EnemyComponent.h"
#include "Components/ScoreComponent.h"

void dae::EnemyTracker::RegisterEnemy(dae::EnemyComponent* pEnemyComp)
{
	if(m_pScoreComp != nullptr)
		pEnemyComp->AddObserver(m_pScoreComp);
	m_Enemies.push_back(pEnemyComp);
}

void dae::EnemyTracker::Notify(Utils::GameEvent event, dae::ObserverEventData* eventData)
{
	if(event != Utils::GameEvent::EnemyDied)
		return;

	auto pEnemyDiedData{dynamic_cast<EnemyDiedEvent*>(eventData)};
	UnregisterEnemy(dynamic_cast<EnemyComponent*>(pEnemyDiedData->m_Component));

}

bool dae::EnemyTracker::NoEnemiesLeft() const
{
	return m_Enemies.empty();
}

void dae::EnemyTracker::RegisterScoreComp(ScoreComponent* pScoreComp)
{
	m_pScoreComp = pScoreComp;
	for(auto& enemy : m_Enemies)
	{
		enemy->AddObserver(m_pScoreComp);
	}
}

void dae::EnemyTracker::ResetEnemies()
{
	m_Enemies.clear();
}

void dae::EnemyTracker::UnregisterEnemy(EnemyComponent* pEnemyComp)
{
	m_Enemies.erase(std::remove(m_Enemies.begin(), m_Enemies.end(), pEnemyComp), m_Enemies.end());
}
