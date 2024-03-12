#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <SDL.h>
#include "InputManager.h"

#include <iostream>
#include <SDL_syswm.h>

#include "Controller.h"
#include "../imgui-1.89.5/backends/imgui_impl_sdl2.h"


bool dae::InputManager::ProcessInput()
{


	m_Controller->ProcessInput();
	if(m_Controller->IsPressed(XINPUT_GAMEPAD_B)) std::cout << "B button Pressed\n";
	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		if(e.type == SDL_QUIT)
		{
			return false;
		}
		if(e.type == SDL_KEYDOWN)
		{

		}
		if(e.type == SDL_MOUSEBUTTONDOWN)
		{

		}
		// etc...
		ImGui_ImplSDL2_ProcessEvent(&e);
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
