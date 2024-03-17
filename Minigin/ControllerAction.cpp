#include "ControllerAction.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#pragma comment(lib, "XInput.lib")
dae::ControllerAction::ControllerAction(ActionType type, std::unique_ptr<dae::Command> command, unsigned buttonMap) :
	m_Command{std::move(command)},
	m_ButtonMap{buttonMap},
	m_Type{type}
{
	
}

dae::Command* dae::ControllerAction::GetCommand() const
{
	return m_Command.get();
}

unsigned dae::ControllerAction::GetButtonMapping() const
{
	return m_ButtonMap;
}

dae::ControllerAction::ActionType dae::ControllerAction::GetType() const
{
	return m_Type;
}

