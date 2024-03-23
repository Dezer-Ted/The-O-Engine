#pragma once
#include "Command.h"
#include "Controller.h"

namespace dae
{
	class ControllerCompoundAction {
	public:
		ControllerCompoundAction(Controller::ButtonInputs upInput, Controller::ButtonInputs    downInput, Controller::ButtonInputs leftInput,
		                         Controller::ButtonInputs rightInput, std::unique_ptr<Command> pCommand, Controller*               pController);
		ControllerCompoundAction(const ControllerCompoundAction&) = delete;
		ControllerCompoundAction(ControllerCompoundAction&&) = delete;
		ControllerCompoundAction& operator=(const ControllerCompoundAction&) = delete;
		ControllerCompoundAction& operator=(ControllerCompoundAction&&) = delete;
		~ControllerCompoundAction() = default;
		void HandleButtonInput() const;

	private:
		Controller*                   m_pController;
		std::unique_ptr<dae::Command> m_pCommand;
		Controller::ButtonInputs      m_UpInput;
		Controller::ButtonInputs      m_DownInput;
		Controller::ButtonInputs      m_RightInput;
		Controller::ButtonInputs      m_LeftInput;
	};
}
