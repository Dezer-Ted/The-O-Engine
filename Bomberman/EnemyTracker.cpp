#include "EnemyTracker.h"

#include "Components/EnemyComponent.h"

void dae::EnemyTracker::RegisterEnemy(dae::EnemyComponent* pEnemyComp)
{
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

void dae::EnemyTracker::UnregisterEnemy(EnemyComponent* pEnemyComp)
{
	m_Enemies.erase(std::remove(m_Enemies.begin(), m_Enemies.end(), pEnemyComp), m_Enemies.end());
}
