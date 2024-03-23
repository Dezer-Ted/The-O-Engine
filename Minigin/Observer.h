#pragma once
#include "Utils.h"


namespace dae
{


	class BaseComponent;

	class Observer {
	public:
		virtual      ~Observer() = default;
		virtual void Notify(Utils::GameEvent event, BaseComponent* components) = 0;
	};
}
