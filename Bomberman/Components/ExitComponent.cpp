#include "ExitComponent.h"

#include "../EnemyTracker.h"
#include "../SceneNavigator.h"
#include "Components/ColliderComponent.h"

dae::ExitComponent::ExitComponent(GameObject* pParent)
	: BaseComponent(pParent)
{
}

void dae::ExitComponent::Notify(Utils::GameEvent event, ObserverEventData* eventData)
{
	if(event == Utils::GameEvent::Collision)
	{
		auto pCollComp{dynamic_cast<CollisionEventData*>(eventData)};
		if(!EnemyTracker::GetInstance().NoEnemiesLeft())
			return;
		if(pCollComp->m_OtherCollider->GetParentTag() != "Player")
			return;
		SceneNavigator::UnloadStage();
	}
}
