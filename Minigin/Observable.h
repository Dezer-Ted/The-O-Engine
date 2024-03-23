#pragma once
#include <vector>

#include "Utils.h"

namespace dae
{
	class Observer;
	class Observable {
	public:
		virtual ~Observable()
		{
		}

		virtual void AddObserver(Observer* pObserver);
		void RemoveObserver(Observer* pObserver);
	protected:
		void NotifyObservers(Utils::GameEvent event,BaseComponent* component) const;
	private:
		std::vector<Observer*> m_Observers;
	};
}
