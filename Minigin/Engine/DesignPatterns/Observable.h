#pragma once
#include <any>
#include <vector>

#include "../ObserverEventData.h"
#include "../Utils/Utils.h"


namespace dae
{
	class Observer;
	class BaseComponent;
	class Blackboard;
	class Observable {
	public:
		virtual ~Observable();

		virtual void AddObserver(Observer* pObserver);
		void RemoveObserver(Observer* pObserver);
	protected:
		void NotifyObservers(Utils::GameEvent event,std::unique_ptr<ObserverEventData> eventData) const;
	private:
		std::vector<Observer*> m_Observers;
	};
}
