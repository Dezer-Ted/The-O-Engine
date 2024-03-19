#pragma once
#include <memory>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>

#pragma comment(lib, "XInput.lib")
#include "Command.h"
#include "Controller.h"

namespace dae
{
	class ControllerAction {
	public:
		enum class ActionType {
			ButtonMap,
			RightAnalogStick,
			LeftAnalogStick,
		};

		ControllerAction(ActionType type, std::unique_ptr<dae::Command> command, Controller::ButtonInputs button);
		ControllerAction(ActionType type, std::unique_ptr<dae::Command> command);
		dae::Command*            GetCommand() const;
		Controller::ButtonInputs GetButtonMapping() const;
		ActionType               GetType() const;

	private:
		std::unique_ptr<dae::Command> m_Command;
		Controller::ButtonInputs      m_ButtonMap{0};
		ActionType                    m_Type;
	};
}
