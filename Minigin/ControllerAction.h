#pragma once
#include <memory>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>

#pragma comment(lib, "XInput.lib")
#include "Command.h"

namespace dae
{
	class ControllerAction {
	public:
		enum class ActionType {
			ButtonMap,
			RightAnalogStick,
			LeftAnalogStick,
		};

		ControllerAction(ActionType type, std::unique_ptr<dae::Command> command, unsigned int buttonMap = 0);
		dae::Command* GetCommand() const;
		unsigned int  GetButtonMapping() const;
		ActionType    GetType() const;

	private:
		std::unique_ptr<dae::Command> m_Command;
		unsigned int                  m_ButtonMap;
		ActionType                    m_Type;
	};
}
