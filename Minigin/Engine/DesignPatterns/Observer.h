#pragma once
#include <any>

#include "../Utils/Utils.h"


namespace dae
{
	class BaseComponent;

	class Observer {
	public:
		virtual      ~Observer() = default;
		virtual void Notify(Utils::GameEvent event, std::unique_ptr<ObserverEventData> eventData) = 0;
	};
}
