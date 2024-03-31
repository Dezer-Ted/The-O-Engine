#pragma once
#include <memory>
#include <SDL_scancode.h>

#include "../../Engine/DesignPatterns/Command.h"

namespace dae
{
	class KeyboardAction {
	public:
		enum class ActionType {
			ButtonMap,
			WASDMovement
		};

		enum class InputType {
			OnButtonDown,
			OnButtonUp,
			WhilePressed
		};

		KeyboardAction(InputType inputType, ActionType type, std::unique_ptr<Command> command, SDL_Scancode buttonMap);
		KeyboardAction(InputType inputType, ActionType type, std::unique_ptr<Command> command);

		Command*     GetCommand() const;
		ActionType   GetActionType() const;
		SDL_Scancode GetButtonMap() const;
		InputType    GetInputType() const;
		bool GetIsPressed() const;
		void SetIsPressed(bool isPressed);

	private:
		std::unique_ptr<Command> m_Command;
		SDL_Scancode             m_ButtonMap{SDL_SCANCODE_F};
		ActionType               m_ActionType;
		InputType                m_InputType;
		bool                     m_IsPressed{false};
	};
}
