#pragma once
#include <memory>

#include "../Sound/SoundSystem.h"
#include "../Sound/SDLSoundSystem.h"
namespace dae
{
	class ServiceLocator final {
	public:
		static void              RegisterSoundSystem(std::unique_ptr<dae::SoundSystem>&& instance);
		static dae::SoundSystem* GetSoundSystem();

	private:
		inline static std::unique_ptr<dae::SoundSystem> SoundSystemInstance;
	};
}
