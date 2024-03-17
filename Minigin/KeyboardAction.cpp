#include "KeyboardAction.h"

dae::KeyboardAction::KeyboardAction(ActionType type, std::unique_ptr<Command> command, SDL_Scancode buttonMap) :
	m_Command{std::move(command)},
	m_ButtonMap{buttonMap},
	m_Type{type}
{
}

dae::Command* dae::KeyboardAction::GetCommand() const
{
	return m_Command.get();
}

dae::KeyboardAction::ActionType dae::KeyboardAction::GetType() const
{
	return m_Type;
}

SDL_Scancode dae::KeyboardAction::GetButtonMap() const
{
	return m_ButtonMap;
}
