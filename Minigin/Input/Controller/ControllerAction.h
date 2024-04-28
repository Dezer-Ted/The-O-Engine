#pragma once
#include <memory>

#include "../../Engine/DesignPatterns/Command.h"
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

		enum class InputType {
			ButtonDown,
			ButtonUp,
			ButtonPressed
		};

		ControllerAction(ActionType actionType, std::unique_ptr<dae::Command> command, Controller::ButtonInputs button, InputType inputType);
		ControllerAction(ActionType type, std::unique_ptr<dae::Command> command);
		~ControllerAction();
		dae::Command*            GetCommand() const;
		Controller::ButtonInputs GetButtonMapping() const;
		ActionType               GetType() const;
		InputType                GetInpuType() const;

	private:
		std::unique_ptr<dae::Command> m_Command;
		Controller::ButtonInputs      m_ButtonMap{};
		ActionType                    m_Type;
		InputType                     m_InputType{};
	};
}
