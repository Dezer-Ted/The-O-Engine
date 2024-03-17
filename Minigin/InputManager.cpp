#include <SDL.h>
#include "InputManager.h"

#include <iostream>
#include <SDL_syswm.h>

#include "Controller.h"
#include "../imgui-1.89.5/backends/imgui_impl_sdl2.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>

#pragma comment(lib, "XInput.lib")

bool dae::InputManager::ProcessInput()
{


	m_Controller->ProcessInput();
	ProcessControllerActions();
	return ProcessKeyboardActions();
}

void dae::InputManager::ProcessControllerActions() const
{
	for(auto& action : m_ControllerActions)
	{
		switch(action->GetType())
		{
		case ControllerAction::ActionType::ButtonMap:
			if(m_Controller->IsDownThisFrame(action->GetButtonMapping())) action->GetCommand()->Execute();
			break;
		case ControllerAction::ActionType::LeftAnalogStick:
			action->GetCommand()->ExecuteMovement(m_Controller->GetLeftAnalogStick());
			break;
		case ControllerAction::ActionType::RightAnalogStick:
			action->GetCommand()->ExecuteMovement(m_Controller->GetRightAnalogStick());
			break;
		}
	}
}

bool dae::InputManager::ProcessKeyboardActions()
{
	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		if(e.type == SDL_QUIT)
		{
			return false;
		}
		if(e.type == SDL_KEYDOWN)
		{
			switch(e.key.keysym.scancode)
			{
			case SDL_SCANCODE_W:
				wasdInput.wButton = true;
				break;
			case SDL_SCANCODE_A:
				wasdInput.aButton = true;
				break;
			case SDL_SCANCODE_S:
				wasdInput.sButton = true;
				break;
			case SDL_SCANCODE_D:
				wasdInput.dButton = true;
				break;
			}
			for(auto& action : m_KeyBoardActions)
			{
				if(action->GetType() != KeyboardAction::ActionType::ButtonMap) break;
				if(e.key.keysym.scancode == action->GetButtonMap())
				{
					action->GetCommand()->Execute();
				}

			}
		}
		if(e.type == SDL_KEYUP)
		{
			switch(e.key.keysym.scancode)
			{
			case SDL_SCANCODE_W:
				wasdInput.wButton = false;
				break;
			case SDL_SCANCODE_A:
				wasdInput.aButton = false;
				break;
			case SDL_SCANCODE_S:
				wasdInput.sButton = false;
				break;
			case SDL_SCANCODE_D:
				wasdInput.dButton = false;
				break;
			}
		}
		if(e.type == SDL_MOUSEBUTTONDOWN)
		{

		}
		// etc...
		ImGui_ImplSDL2_ProcessEvent(&e);
	}
	ProcessWASDInput();
	for(auto& action : m_KeyBoardActions)
	{
		if(action->GetType() == KeyboardAction::ActionType::WASDMovement)
		{
			action->GetCommand()->ExecuteMovement(m_WASDInput);
		}
	}
	return true;
}

dae::InputManager::InputManager()
	: Singleton<dae::InputManager>()
{
	m_Controller = std::make_unique<Controller>();
}

dae::InputManager::~InputManager()
{

}

void dae::InputManager::ProcessWASDInput()
{
	m_WASDInput = glm::vec2{};
	if(wasdInput.aButton) m_WASDInput.x -= 1.f;
	if(wasdInput.dButton) m_WASDInput.x += 1.f;
	if(wasdInput.wButton) m_WASDInput.y -= 1.f;
	if(wasdInput.sButton) m_WASDInput.y += 1.f;
}
