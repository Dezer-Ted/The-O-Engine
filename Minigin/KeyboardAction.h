#pragma once
#include <memory>
#include <SDL_scancode.h>

#include "Command.h"

namespace dae
{
	class KeyboardAction {
	public:
		enum class ActionType {
			ButtonMap,
			WASDMovement
		};

		KeyboardAction(ActionType type, std::unique_ptr<Command> command, SDL_Scancode buttonMap = SDL_SCANCODE_F);
		Command*     GetCommand() const;
		ActionType   GetType() const;
		SDL_Scancode GetButtonMap() const;

	private:
		std::unique_ptr<Command> m_Command;
		SDL_Scancode             m_ButtonMap;
		ActionType               m_Type;
	};
}
