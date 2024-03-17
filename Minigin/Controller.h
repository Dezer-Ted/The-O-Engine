#pragma once
#include <memory>
#include <glm/vec2.hpp>

namespace dae
{
	class Controller {
	private:
		class XInputImpl;
		std::unique_ptr<XInputImpl> m_pImpl;

	public:
		void ProcessInput();
		Controller();
		Controller(const Controller&) = delete;
		Controller(Controller&&) = delete;
		Controller& operator=(const Controller&) = delete;
		Controller& operator=(Controller&&) = delete;
		~Controller();

		bool IsDownThisFrame(unsigned int button) const;
		bool IsUpThisFrame(unsigned int button) const;
		bool IsPressed(unsigned int button) const;
		glm::vec2 GetLeftAnalogStick() const;
		glm::vec2 GetRightAnalogStick() const;
	};
}
