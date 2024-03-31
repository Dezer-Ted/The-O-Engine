#include "Controller.h"

#include <SDL_syswm.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>
#include <glm/glm.hpp>

#pragma comment(lib, "XInput.lib")
class dae::Controller::XInputImpl {
	XINPUT_STATE m_CurrentState{};
	XINPUT_STATE m_PreviousState{};
	unsigned int m_ControllerIndex{0};
	unsigned int m_ButtonsReleasedThisFrame{};
	unsigned int m_ButtonsPressedThisFrame{};
	const float  m_DeadZone{0.15f};
	glm::vec2    CheckDeadZones(float xInput, float yInput) const;
	float        RemapAnalogStick(float stickInput) const;

public:
	XInputImpl();
	XInputImpl(const XInputImpl&) = delete;
	XInputImpl(XInputImpl&&) = delete;
	XInputImpl& operator=(const XInputImpl&) = delete;
	XInputImpl& operator=(XInputImpl&&) = delete;
	~XInputImpl() = default;
	void      ProcessInput();
	bool      IsDownThisFrame(unsigned int button) const;
	bool      IsUpThisFrame(unsigned int button) const;
	bool      IsPressed(unsigned int button) const;
	glm::vec2 GetLeftAnalogStick() const;
	glm::vec2 GetRightAnalogStick() const;
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

glm::vec2 dae::Controller::XInputImpl::GetLeftAnalogStick() const
{
	const float normalX = RemapAnalogStick(static_cast<float>(m_CurrentState.Gamepad.sThumbLX));
	const float normalY = -RemapAnalogStick(static_cast<float>(m_CurrentState.Gamepad.sThumbLY));
	return CheckDeadZones(normalX, normalY);
}

glm::vec2 dae::Controller::XInputImpl::GetRightAnalogStick() const
{
	const float normalX = RemapAnalogStick(static_cast<float>(m_CurrentState.Gamepad.sThumbRX));
	const float normalY = -RemapAnalogStick(static_cast<float>(m_CurrentState.Gamepad.sThumbRY));

	return CheckDeadZones(normalX, normalY);
}

glm::vec2 dae::Controller::XInputImpl::CheckDeadZones(float xInput, float yInput) const
{
	const float stickX{abs(xInput) < m_DeadZone ? 0 : xInput};
	const float stickY{abs(yInput) < m_DeadZone ? 0 : yInput};
	return glm::vec2{stickX, stickY};
}

float dae::Controller::XInputImpl::RemapAnalogStick(float stickInput) const
{
	return fmaxf(-1, stickInput / 32767);
}

dae::Controller::Controller()
{
	m_pImpl = std::make_unique<XInputImpl>();
}

dae::Controller::~Controller()
{

}

glm::vec2 dae::Controller::GetRightAnalogStick() const
{
	return m_pImpl->GetRightAnalogStick();
}

unsigned dae::Controller::TranslateToXInput(ButtonInputs button) const
{
	switch(button)
	{
	case ButtonInputs::AButton:
		return XINPUT_GAMEPAD_A;
	case ButtonInputs::BButton:
		return XINPUT_GAMEPAD_B;
	case ButtonInputs::XButton:
		return XINPUT_GAMEPAD_X;
	case ButtonInputs::YButton:
		return XINPUT_GAMEPAD_Y;
	case ButtonInputs::RBButton:
		return XINPUT_GAMEPAD_RIGHT_SHOULDER;
	case ButtonInputs::LBButton:
		return XINPUT_GAMEPAD_LEFT_SHOULDER;
	case ButtonInputs::DPadUp:
		return XINPUT_GAMEPAD_DPAD_UP;
	case ButtonInputs::DPadDown:
		return XINPUT_GAMEPAD_DPAD_DOWN;
	case ButtonInputs::DPadLeft:
		return XINPUT_GAMEPAD_DPAD_LEFT;
	case ButtonInputs::DPadRight:
		return XINPUT_GAMEPAD_DPAD_RIGHT;
	case ButtonInputs::SelectButton:
		return XINPUT_GAMEPAD_BACK;
	case ButtonInputs::StartButton:
		return XINPUT_GAMEPAD_START;
	}
	return 0;
}

bool dae::Controller::IsDownThisFrame(ButtonInputs button) const
{
	return m_pImpl->IsDownThisFrame(TranslateToXInput(button));
}

bool dae::Controller::IsUpThisFrame(ButtonInputs button) const
{
	return m_pImpl->IsUpThisFrame(TranslateToXInput(button));
}

bool dae::Controller::IsPressed(ButtonInputs button) const
{
	return m_pImpl->IsPressed(TranslateToXInput(button));
}

glm::vec2 dae::Controller::GetLeftAnalogStick() const
{
	return m_pImpl->GetLeftAnalogStick();
}
