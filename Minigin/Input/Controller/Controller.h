#pragma once
#include <memory>
#include <glm/vec2.hpp>

namespace dae
{
	class Controller {
	public:
		enum class ButtonInputs {
			AButton,
			BButton,
			XButton,
			YButton,
			RBButton,
			LBButton,
			DPadUp,
			DPadDown,
			DPadLeft,
			DPadRight,
			SelectButton,
			StartButton
		};
		
		void ProcessInput();
		Controller();
		Controller(const Controller&) = delete;
		Controller(Controller&&) = delete;
		Controller& operator=(const Controller&) = delete;
		Controller& operator=(Controller&&) = delete;
		~Controller();

		bool      IsDownThisFrame(ButtonInputs button) const;
		bool      IsUpThisFrame(ButtonInputs button) const;
		bool      IsPressed(ButtonInputs button) const;
		glm::vec2 GetLeftAnalogStick() const;
		glm::vec2 GetRightAnalogStick() const;

	private:
		unsigned int TranslateToXInput(ButtonInputs button) const;
		class XInputImpl;
		std::unique_ptr<XInputImpl> m_pImpl;
	};
}
