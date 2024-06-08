#include "KeyboardAction.h"
#include "../InputManager.h"

dae::KeyboardAction::KeyboardAction(InputType inputType, ActionType type, std::unique_ptr<Command> command, SDL_Scancode buttonMap) :
	m_Command{std::move(command)},
	m_ButtonMap{buttonMap},
	m_ActionType{type},
	m_InputType(inputType)
{
}

dae::KeyboardAction::KeyboardAction(InputType inputType, ActionType type, std::unique_ptr<Command> command) :
	m_Command(std::move(command)),
	m_ActionType(type),
	m_InputType(inputType)
{

}

dae::KeyboardAction::~KeyboardAction()
{

}

dae::Command* dae::KeyboardAction::GetCommand() const
{
	return m_Command.get();
}

dae::KeyboardAction::ActionType dae::KeyboardAction::GetActionType() const
{
	return m_ActionType;
}

dae::KeyboardAction::InputType dae::KeyboardAction::GetInputType() const
{
	return m_InputType;
}

bool dae::KeyboardAction::GetIsPressed() const
{
	return m_IsPressed;
}

void dae::KeyboardAction::SetIsPressed(bool isPressed)
{
	m_LastState = m_IsPressed;
	m_IsPressed = isPressed;
}

bool dae::KeyboardAction::GetLastState() const
{
	return m_LastState;
}


SDL_Scancode dae::KeyboardAction::GetButtonMap() const
{
	return m_ButtonMap;
}
