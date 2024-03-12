#include "Controller.h"

#include <SDL_syswm.h>
class dae::Controller::XInputImpl {
	XINPUT_STATE m_CurrentState;
	XINPUT_STATE m_PreviousState;
	unsigned int m_ControllerIndex{};
	unsigned int m_ButtonsReleasedThisFrame{};
	unsigned int m_ButtonsPressedThisFrame{};

public:
	XInputImpl();
	XInputImpl(const XInputImpl&) = delete;
	XInputImpl(XInputImpl&&) = delete;
	XInputImpl& operator=(const XInputImpl&) = delete;
	XInputImpl& operator=(XInputImpl&&) = delete;
	~XInputImpl() = default;
	void ProcessInput();
	bool IsDownThisFrame(unsigned int button) const;
	bool IsUpThisFrame(unsigned int button) const;
	bool IsPressed(unsigned int button) const;
};

void dae::Controller::ProcessInput()
{
	m_pImpl->ProcessInput();
}


dae::Controller::XInputImpl::XInputImpl()
{

}

void dae::Controller::XInputImpl::ProcessInput()
{
	CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(m_ControllerIndex, &m_CurrentState);

	auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
	m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
	m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
}

bool dae::Controller::XInputImpl::IsDownThisFrame(unsigned button) const
{
	return m_ButtonsPressedThisFrame & button;
}

bool dae::Controller::XInputImpl::IsUpThisFrame(unsigned button) const
{
	return m_ButtonsReleasedThisFrame & button;
}

bool dae::Controller::XInputImpl::IsPressed(unsigned button) const
{
	return m_CurrentState.Gamepad.wButtons & button;
}

dae::Controller::Controller()
{

}

dae::Controller::~Controller()
{
	
}

bool dae::Controller::IsDownThisFrame(unsigned button)
{
	return m_pImpl->IsDownThisFrame(button);
}

bool dae::Controller::IsUpThisFrame(unsigned button)
{
	return m_pImpl->IsUpThisFrame(button);
}

bool dae::Controller::IsPressed(unsigned button)
{
	return m_pImpl->IsPressed(button);
}
