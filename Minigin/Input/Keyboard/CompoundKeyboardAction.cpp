#include "CompoundKeyboardAction.h"

void dae::CompoundKeyboardAction::HandleKeyDown(SDL_Event e)
{
	if(e.key.keysym.scancode == m_UpButton) m_UpIspressed = true;
	if(e.key.keysym.scancode == m_DownButton) m_DownIsPressed = true;
	if(e.key.keysym.scancode == m_LeftButton) m_LeftIsPressed = true;
	if(e.key.keysym.scancode == m_RightButton) m_RightIsPressed = true;
}

void dae::CompoundKeyboardAction::ExecuteCommand()
{
	m_pCommand->Execute2DAxis(ConvertTo2DVector());
}

glm::vec2 dae::CompoundKeyboardAction::ConvertTo2DVector()
{
	glm::vec2 result{};
	if(m_UpIspressed) result.y -= 1;
	if(m_DownIsPressed) result.y += 1;
	if(m_RightIsPressed) result.x += 1;
	if(m_LeftIsPressed) result.x -= 1;
	return result;

}

SDL_Scancode dae::CompoundKeyboardAction::GetUpButton() const
{
	return m_UpButton;
}

SDL_Scancode dae::CompoundKeyboardAction::GetDownButton() const
{
	return m_DownButton;
}

SDL_Scancode dae::CompoundKeyboardAction::GetLeftButton() const
{
	return m_LeftButton;
}

SDL_Scancode dae::CompoundKeyboardAction::GetRightButton() const
{
	return m_RightButton;
}

dae::CompoundKeyboardAction::CompoundKeyboardAction(SDL_Scancode                  up, SDL_Scancode down, SDL_Scancode right, SDL_Scancode left,
                                                    std::unique_ptr<dae::Command> pCommand) :
	m_pCommand(std::move(pCommand)),
	m_UpButton(up),
	m_DownButton(down),
	m_RightButton(right),
	m_LeftButton(left)
{

}

void dae::CompoundKeyboardAction::HandleKeyUp(SDL_Event e)
{
	if(e.key.keysym.scancode == m_UpButton) m_UpIspressed = false;
	if(e.key.keysym.scancode == m_DownButton) m_DownIsPressed = false;
	if(e.key.keysym.scancode == m_LeftButton) m_LeftIsPressed = false;
	if(e.key.keysym.scancode == m_RightButton) m_RightIsPressed = false;
}
