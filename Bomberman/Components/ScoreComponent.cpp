#include "ScoreComponent.h"

#include "EnemyComponent.h"
#include "../EnemyTracker.h"
#include "../PersistentData.h"
#include "../SceneNavigator.h"
#include "Components/TextComponent.h"

dae::ScoreComponent::ScoreComponent(GameObject* pParent) : BaseComponent(pParent)
{
	m_pTextComp = GetParent()->GetComponentByClass<TextComponent>();
	m_ScoreMap[EnemyType::Balloom] = 100;
	m_ScoreMap[EnemyType::Oneal] = 200;
	m_ScoreMap[EnemyType::Doll] = 400;
	m_ScoreMap[EnemyType::Minvo] = 800;
	EnemyTracker::GetInstance().RegisterScoreComp(this);
	const int persistentScore{PersistentData::GetInstance().GetScore()};
	if(persistentScore != 0)
		m_Score = persistentScore;
	m_pTextComp->SetText(std::to_string(m_Score));
}

void dae::ScoreComponent::Notify(Utils::GameEvent event, ObserverEventData* eventData)
{
	if(event != Utils::GameEvent::EnemyDied)
		return;
	auto enemyDiedEventData{dynamic_cast<EnemyDiedEvent*>(eventData)};
	m_Score += m_ScoreMap[enemyDiedEventData->m_Type];
	m_pTextComp->SetText(std::to_string(m_Score));
}

dae::ScoreComponent::~ScoreComponent()
{
	if(SceneNavigator::m_LevelCompleted || PersistentData::GetInstance().GetLifes() == 0)
		PersistentData::GetInstance().SetScore(m_Score);
}
