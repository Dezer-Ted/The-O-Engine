#include "Observable.h"

#include "Observer.h"

void dae::Observable::AddObserver(Observer* pObserver)
{
	m_Observers.push_back(pObserver);
}

void dae::Observable::RemoveObserver(Observer* pObserver)
{
	m_Observers.erase(std::find(m_Observers.begin(),m_Observers.end(),pObserver));
}

void dae::Observable::NotifyObservers(Utils::GameEvent event,BaseComponent* component) const
{
	for(auto& observer : m_Observers)
	{
		observer->Notify(event,component);
	}
}
