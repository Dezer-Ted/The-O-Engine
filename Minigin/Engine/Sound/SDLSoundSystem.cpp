#include "SDLSoundSystem.h"

#include <iostream>

#include "../ResourceManager.h"

dae::SDLSoundSystem::~SDLSoundSystem()
{
	Mix_CloseAudio();
}

void dae::SDLSoundSystem::Play(const std::string& soundName, int volume = 64)
{

	if(m_SoundMap.contains(soundName))
	{
		m_SoundMap[soundName]->PlaySoundEffect(volume);
	}
	else
	{
		m_SoundMap[soundName] = ResourceManager::GetInstance().LoadSound(soundName);
		m_SoundMap[soundName]->PlaySoundEffect(volume);
	}
}

dae::SDLSoundSystem::SDLSoundSystem()
{
	if(Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		std::cout << "SDL2_Mixer could not be initialized!\n";
		return;
	}

}
