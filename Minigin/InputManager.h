#pragma once
#include <memory>
#include <vector>

#include "CompoundKeyboardAction.h"
#include "ControllerAction.h"
#include "GameObject.h"
#include "KeyboardAction.h"
#include "Singleton.h"
#include "ControllerCompoundAction.h"

namespace dae
{
	class Controller;

	class InputManager final : public Singleton<InputManager> {
	private:
		std::unique_ptr<Controller>                          m_Controller;
		std::vector<std::unique_ptr<ControllerAction>>       m_ControllerActions;
		std::vector<std::unique_ptr<KeyboardAction>>         m_KeyBoardActions;
		std::vector<std::unique_ptr<CompoundKeyboardAction>> m_CompoundKeyboardActions;
		std::vector<std::unique_ptr<ControllerCompoundAction>> m_CompoundControllerActions;

	public:
		void AddControllerCompoundAction(Controller::ButtonInputs upInput,Controller::ButtonInputs downInput,Controller::ButtonInputs leftInput,Controller::ButtonInputs rightInput, GameObject* go);
		void AddCompoundKeyboardAction(SDL_Scancode up, SDL_Scancode down, SDL_Scancode left, SDL_Scancode right, GameObject* pOwner);

		template <typename T>
		void AddControllerActionMapping(ControllerAction::ActionType type, GameObject* gameObject, Controller::ButtonInputs buttonMap, ControllerAction::InputType inputType)
		{
			m_ControllerActions.push_back(std::make_unique<ControllerAction>(type, std::move(std::make_unique<T>(gameObject)),buttonMap,inputType));
		}

		template <typename T>
		void AddKeyBoardActionMapping(KeyboardAction::ActionType type, GameObject* gameObject, SDL_Scancode = SDL_SCANCODE_F)
		{
			m_KeyBoardActions.push_back(std::make_unique<KeyboardAction>(type, std::move(std::make_unique<T>(gameObject))));
		}

		template <typename T>
		void RemoveKeyboardActionMapping()
		{
			try
			{
				for(int i = 0; i < m_KeyBoardActions.size(); ++i)
				{
					T* castedAction = dynamic_cast<T*>(m_KeyBoardActions[i].get());
					if(castedAction != nullptr) m_KeyBoardActions.erase(m_KeyBoardActions.begin() + i);
				}
			}
			catch(...)
			{
				std::cout << "No Keyboard Action of this type could be found \n";
			}

		}

		template <typename T>
		void RemoveControllerActionMapping()
		{
			try
			{
				for(int i = 0; i < m_ControllerActions.size(); ++i)
				{
					T* castedAction = dynamic_cast<T*>(m_ControllerActions[i].get());
					if(castedAction != nullptr) m_ControllerActions.erase(m_ControllerActions.begin() + i);
				}
			}
			catch(...)
			{
				std::cout << "No ControllerAction of this type could be found \n";
			}

		}

		bool ProcessInput();
		void ControllerProcessInputType(const std::vector<std::unique_ptr<dae::ControllerAction>>::value_type& action) const;
		void ProcessControllerActions() const;
		void HandlKeyboardButtonActions(const SDL_Event& e, KeyboardAction::InputType input);
		bool ProcessKeyboardActions();
		InputManager();
		~InputManager() override;
		void HandleIsPressedInputs(bool IsButtonDown, const SDL_Event& e) const;
		void ExecuteIsPressedInputs();
		void ProcessControllerCompoundActions() const;
	};
}
