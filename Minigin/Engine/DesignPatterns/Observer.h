#pragma once
#include <any>

#include "../Utils/Utils.h"
#include "../ObserverEventData.h"


namespace dae
{
	class BaseComponent;

	class Observer {
	public:
		virtual      ~Observer() = default;
		virtual void Notify(Utils::GameEvent event, ObserverEventData* eventData) = 0;
	};
}
