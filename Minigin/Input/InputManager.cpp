#include <SDL.h>
#include "InputManager.h"


#include "Controller/Controller.h"
#include "../imgui-1.89.5/backends/imgui_impl_sdl2.h"


void dae::InputManager::WipeActions()
{
	m_ControllerActions.clear();
	m_KeyBoardActions.clear();
	m_CompoundKeyboardActions.clear();
	m_CompoundControllerActions.clear();
}

bool dae::InputManager::ProcessInput()
{


	m_Controller->ProcessInput();
	ProcessControllerActions();
	ProcessControllerCompoundActions();
	return ProcessKeyboardActions();
}

void dae::InputManager::ControllerProcessInputType(const std::vector<std::unique_ptr<dae::ControllerAction>>::value_type& action) const
{
	switch(action->GetInpuType())
	{
	case ControllerAction::InputType::ButtonDown:
		if(m_Controller->IsDownThisFrame(action->GetButtonMapping()))
			action->GetCommand()->Execute();
		break;
	case ControllerAction::InputType::ButtonUp:
		if(m_Controller->IsUpThisFrame(action->GetButtonMapping()))
			action->GetCommand()->Execute();
		break;
	case ControllerAction::InputType::ButtonPressed:
		if(m_Controller->IsPressed(action->GetButtonMapping()))
			action->GetCommand()->Execute();
		break;
	}
}

void dae::InputManager::ProcessControllerActions() const
{
	for(auto& action : m_ControllerActions)
	{
		switch(action->GetType())
		{
		case ControllerAction::ActionType::ButtonMap:
			ControllerProcessInputType(action);
		case ControllerAction::ActionType::LeftAnalogStick:
			action->GetCommand()->Execute2DAxis(m_Controller->GetLeftAnalogStick());
			break;
		case ControllerAction::ActionType::RightAnalogStick:
			action->GetCommand()->Execute2DAxis(m_Controller->GetRightAnalogStick());
			break;
		}
	}
}

void dae::InputManager::HandlKeyboardButtonActions(const SDL_Event& e, dae::KeyboardAction::InputType input)
{
	for(auto& action : m_KeyBoardActions)
	{
		if(action->GetInputType() != input)
			continue;
		if(action->GetActionType() != KeyboardAction::ActionType::ButtonMap)
			continue;
		if(e.key.keysym.scancode == action->GetButtonMap())
		{
			if(action->GetIsPressed())
				continue;
			action->SetIsPressed(true);

			action->GetCommand()->Execute();
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
			HandleIsPressedInputs(false, e);
		}
		if(e.type == SDL_MOUSEBUTTONDOWN)
		{

		}
		ImGui_ImplSDL2_ProcessEvent(&e);
	}
	for(auto& keyAction : m_KeyBoardActions)
	{
		switch(keyAction->GetInputType())
		{
		case KeyboardAction::InputType::OnButtonDown:
			if(!keyAction->GetLastState() && keyAction->GetIsPressed())
				keyAction->GetCommand()->Execute();
			break;
		case KeyboardAction::InputType::OnButtonUp:
			if(keyAction->GetLastState() && !keyAction->GetIsPressed())
				keyAction->GetCommand()->Execute();
			break;
		case KeyboardAction::InputType::WhilePressed:
			if(keyAction->GetIsPressed())
				keyAction->GetCommand()->Execute();
			break;
		}


	}
	for(auto& compoundkeyboardAction : m_CompoundKeyboardActions)
	{
		compoundkeyboardAction->ExecuteCommand();
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

void dae::InputManager::HandleIsPressedInputs(bool IsButtonDown, const SDL_Event& e) const
{
	for(auto& action : m_KeyBoardActions)
	{
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
		if(action->GetInputType() != KeyboardAction::InputType::WhilePressed)
			continue;
		if(action->GetIsPressed())
		{
			action->GetCommand()->Execute();
		}
	}
}

void dae::InputManager::ProcessControllerCompoundActions() const
{
	for(auto& compoundAction : m_CompoundControllerActions)
	{
		compoundAction->HandleButtonInput();
	}
}
