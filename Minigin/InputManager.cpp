#include <SDL.h>
#include "InputManager.h"

#include <iostream>
#include <SDL_syswm.h>

#include "Controller.h"
#include "../imgui-1.89.5/backends/imgui_impl_sdl2.h"


void dae::InputManager::AddCompoundKeyboardAction(SDL_Scancode up, SDL_Scancode down, SDL_Scancode left, SDL_Scancode right, GameObject* pOwner)
{
	m_CompoundKeyboardActions.push_back(std::make_unique<CompoundKeyboardAction>(up, down, right, left, std::move(std::make_unique<Move>(pOwner))));
}

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
			action->GetCommand()->Execute2DAxis(m_Controller->GetLeftAnalogStick());
			break;
		case ControllerAction::ActionType::RightAnalogStick:
			action->GetCommand()->Execute2DAxis(m_Controller->GetRightAnalogStick());
			break;
		}
	}
}

void dae::InputManager::WASDKeyUp(const SDL_Event& e)
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

void dae::InputManager::WASDKeyDown(const SDL_Event& e)
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
}

void dae::InputManager::HandlKeyboardButtonActions(const SDL_Event& e, dae::KeyboardAction::InputType input)
{
	for(auto& action : m_KeyBoardActions)
	{
		if(action->GetInputType() != input) continue;
		if(action->GetActionType() != KeyboardAction::ActionType::ButtonMap) continue;
		if(e.key.keysym.scancode == action->GetButtonMap())
		{

			action->GetCommand()->Execute();
		}

	}
}


void dae::InputManager::HandleWASDActions()
{
	for(auto& action : m_KeyBoardActions)
	{
		if(action->GetActionType() == KeyboardAction::ActionType::WASDMovement)
		{
			action->GetCommand()->Execute2DAxis(m_WASDInput);
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
			WASDKeyDown(e);
			HandlKeyboardButtonActions(e, KeyboardAction::InputType::OnButtonDown);
			HandleIsPressedInputs(true, e);
			for(auto& compoundkeyboardAction : m_CompoundKeyboardActions)
			{
				compoundkeyboardAction->HandleKeyDown(e);
			}
		}
		if(e.type == SDL_KEYUP)
		{
			for(auto& compoundkeyboardAction : m_CompoundKeyboardActions)
			{
				compoundkeyboardAction->HandleKeyUp(e);
			}
			WASDKeyUp(e);
			HandlKeyboardButtonActions(e, KeyboardAction::InputType::OnButtonDown);
			HandleIsPressedInputs(false, e);
		}
		if(e.type == SDL_MOUSEBUTTONDOWN)
		{

		}
		// etc...
		ImGui_ImplSDL2_ProcessEvent(&e);
	}
	for(auto& compoundkeyboardAction : m_CompoundKeyboardActions)
	{
		compoundkeyboardAction->ExecuteCommand();
	}
	ProcessWASDInput();
	HandleWASDActions();
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

void dae::InputManager::HandleIsPressedInputs(bool IsButtonDown, const SDL_Event& e) const
{
	for(auto& action : m_KeyBoardActions)
	{
		if(action->GetInputType() != KeyboardAction::InputType::WhilePressed) continue;
		if(e.key.keysym.scancode == action->GetButtonMap())
		{
			if(IsButtonDown)
			{
				action->SetIsPressed(true);
			}
			else
			{
				action->SetIsPressed(false);
			}
		}
	}
}

void dae::InputManager::ExecuteIsPressedInputs()
{
	for(auto& action : m_KeyBoardActions)
	{
		if(action->GetInputType() != KeyboardAction::InputType::WhilePressed) continue;
		if(action->GetIsPressed())
		{
			action->GetCommand()->Execute();
		}
	}
}

void dae::InputManager::ProcessWASDInput()
{
	m_WASDInput = glm::vec2{};
	if(wasdInput.aButton) m_WASDInput.x -= 1.f;
	if(wasdInput.dButton) m_WASDInput.x += 1.f;
	if(wasdInput.wButton) m_WASDInput.y -= 1.f;
	if(wasdInput.sButton) m_WASDInput.y += 1.f;
}
