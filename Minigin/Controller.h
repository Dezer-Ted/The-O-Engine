#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <memory>
#include <Xinput.h>

#pragma comment(lib, "xinput.lib")
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

		bool IsDownThisFrame(unsigned int button);
		bool IsUpThisFrame(unsigned int button);
		bool IsPressed(unsigned int button);
	};
}
