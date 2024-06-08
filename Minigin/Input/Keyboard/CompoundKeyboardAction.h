#pragma once
#include <memory>
#include <SDL.h>

#include "../../Engine/DesignPatterns/Command.h"
#include "../../Engine/DesignPatterns/Observable.h"
#include "../../Engine/DesignPatterns/Observer.h"

namespace dae
{
	class CompoundKeyboardAction final{
	public:
		CompoundKeyboardAction(SDL_Scancode up, SDL_Scancode down, SDL_Scancode right, SDL_Scancode left, std::unique_ptr<dae::Command> pCommand);
		CompoundKeyboardAction(const CompoundKeyboardAction&) = delete;
		CompoundKeyboardAction(CompoundKeyboardAction&&) = delete;
		CompoundKeyboardAction& operator=(const CompoundKeyboardAction&) = delete;
		CompoundKeyboardAction& operator=(CompoundKeyboardAction&&) = delete;
		~CompoundKeyboardAction() ;
		void         HandleKeyUp(SDL_Event e);
		void         HandleKeyDown(SDL_Event e);
		void         ExecuteCommand();
		glm::vec2    ConvertTo2DVector();
		SDL_Scancode GetUpButton() const;
		SDL_Scancode GetDownButton() const;
		SDL_Scancode GetLeftButton() const;
		SDL_Scancode GetRightButton() const;

	private:
		std::unique_ptr<dae::Command> m_pCommand;
		SDL_Scancode                  m_UpButton;
		SDL_Scancode                  m_DownButton;
		SDL_Scancode                  m_RightButton;
		SDL_Scancode                  m_LeftButton;
		bool                          m_UpIspressed{false};
		bool                          m_DownIsPressed{false};
		bool                          m_LeftIsPressed{false};
		bool                          m_RightIsPressed{false};
	};
}
