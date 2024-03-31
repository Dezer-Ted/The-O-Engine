#include "Observable.h"
#include "Blackboard.h"
#include "Observer.h"

dae::Observable::~Observable()
{
}

void dae::Observable::AddObserver(Observer* pObserver)
{
	m_Observers.push_back(pObserver);
}

void dae::Observable::RemoveObserver(Observer* pObserver)
{
	m_Observers.erase(std::find(m_Observers.begin(), m_Observers.end(), pObserver));
}

void dae::Observable::NotifyObservers(Utils::GameEvent event, BaseComponent* component,std::unique_ptr<Blackboard> pBlackboard) const
{
	for(auto& observer : m_Observers)
	{
		observer->Notify(event, component, std::move(pBlackboard));
	}
}
