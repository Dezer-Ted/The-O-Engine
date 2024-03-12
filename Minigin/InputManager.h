#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <memory>
#include "Singleton.h"


namespace dae
{
	class Controller;

	class InputManager final : public Singleton<InputManager> {
	private:
		std::unique_ptr<Controller> m_Controller;

	public:
		bool ProcessInput();
		InputManager();
		~InputManager() override;
	};
}
