#include "ObserverEventData.h"
#include "../Components/BaseComponent.h"
#include "../Components/ColliderComponent.h"

dae::ObserverEventData::ObserverEventData(dae::BaseComponent* component) :
	m_Component(component)
{

}

dae::CollisionEventData::CollisionEventData(BaseComponent* component, ColliderComponent* otherCollider) :
	ObserverEventData(component),
	m_OtherCollider(otherCollider)
{

}
