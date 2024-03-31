#include "ControllerCompoundAction.h"

dae::ControllerCompoundAction::ControllerCompoundAction(Controller::ButtonInputs upInput, Controller::ButtonInputs   downInput,
                                                        Controller::ButtonInputs leftInput, Controller::ButtonInputs rightInput,
                                                        std::unique_ptr<Command> pCommand, Controller*               pController) :
	m_pController(pController),
	m_pCommand(std::move(pCommand)),
	m_UpInput(upInput),
	m_DownInput(downInput),
	m_RightInput(rightInput),
	m_LeftInput(leftInput)
{
}

void dae::ControllerCompoundAction::HandleButtonInput() const
{
	glm::vec2 directionInput{};
	if(m_pController->IsPressed(m_UpInput))directionInput.y-=1;
	if(m_pController->IsPressed(m_DownInput))directionInput.y+=1;
	if(m_pController->IsPressed(m_LeftInput))directionInput.x-=1;
	if(m_pController->IsPressed(m_RightInput))directionInput.x+=1;
	m_pCommand->Execute2DAxis(directionInput);

}
