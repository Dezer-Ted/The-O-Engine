#include "DebugSoundSystem.h"

#include <iostream>

#include "../../Components/TextureComponent.h"

dae::DebugSoundSystem::DebugSoundSystem(std::unique_ptr<SoundSystem>&& realSoundSystem)
{
	m_SoundSystem = std::move(realSoundSystem);
}

void dae::DebugSoundSystem::Play(const std::string& soundName, int volume)
{
	std::cout << "Playing " + soundName + " with volume of " + std::to_string(volume) + "\n";
	m_SoundSystem->Play(soundName, volume);
}

void dae::DebugSoundSystem::PlayMusic(const std::string& soundName)
{
	std::cout << "Player " + soundName + "\n";
	m_SoundSystem->PlayMusic(soundName);
}

void dae::DebugSoundSystem::MuteSoundSystem()
{
	m_SoundSystem->MuteSoundSystem();
}
