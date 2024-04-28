#include "ControllerAction.h"


#pragma comment(lib, "XInput.lib")
dae::ControllerAction::ControllerAction(ActionType type, std::unique_ptr<dae::Command> command,Controller::ButtonInputs button,InputType inputType ) :
	m_Command{std::move(command)},
	m_InputType(inputType),
	m_ButtonMap{button},
	m_Type{type}
{
	
}

dae::ControllerAction::ControllerAction(ActionType type, std::unique_ptr<dae::Command> command) :
	m_Command(std::move(command)),
	m_Type(type)
{
}

dae::ControllerAction::~ControllerAction()
{
	
}

dae::Command* dae::ControllerAction::GetCommand() const
{
	return m_Command.get();
}

dae::Controller::ButtonInputs dae::ControllerAction::GetButtonMapping() const
{
	return m_ButtonMap;
}

dae::ControllerAction::ActionType dae::ControllerAction::GetType() const
{
	return m_Type;
}

dae::ControllerAction::InputType dae::ControllerAction::GetInpuType() const
{
	return m_InputType;
}

