#include "ServiceLocator.h"

void dae::ServiceLocator::RegisterSoundSystem(std::unique_ptr<dae::SoundSystem>&& instance)
{
	SoundSystemInstance = instance == nullptr ? std::make_unique<DefaultSoundSystem>() : std::move(instance);
}

dae::SoundSystem* dae::ServiceLocator::GetSoundSystem()
{
	return SoundSystemInstance.get();
}
