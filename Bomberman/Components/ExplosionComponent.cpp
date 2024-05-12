#include "ExplosionComponent.h"

void dae::ExplosionComponent::Notify(Utils::GameEvent event, ObserverEventData* eventData)
{
	if(event == Utils::GameEvent::AnimationEnded)
		GetParent()->DestroyObject();
}

dae::ExplosionComponent::ExplosionComponent(GameObject* pParent) : BaseComponent(pParent)
{

}
