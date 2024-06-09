#include "SDLSoundSystem.h"

#include <cassert>
#include <iostream>
#include <algorithm>
#include "../ResourceManager.h"
#include "../../Components/TextureComponent.h"

dae::SDLSoundSystem::~SDLSoundSystem()
{
	Mix_CloseAudio();
	m_IsRunning = false;
	m_Queue.notify_one();
	m_AudioThread.join();
}

void dae::SDLSoundSystem::Play(const std::string& soundName, int volume)
{
	std::lock_guard<std::mutex> lockGuard(m_QueueMutex);
	for(int i = m_Head; i != m_Tail; i = (i + 1) % MAX_PENDING)
	{
		if(m_Pending[i].soundName == soundName)
		{
			m_Pending[i].volume = max(volume, m_Pending[i].volume);
			return;
		}
	}
	assert((m_Tail +1)%MAX_PENDING != m_Head);
	m_Pending[m_Tail].soundName = soundName;
	m_Pending[m_Tail].volume = volume;
	m_Tail = (m_Tail + 1) % MAX_PENDING;
	m_Queue.notify_one();
}

void dae::SDLSoundSystem::Update()
{
	while(true)
	{
		std::unique_lock lock(m_QueueMutex);
		m_Queue.wait(lock, [this] { return m_Head != m_Tail || !m_IsRunning; });
		if(!m_IsRunning)
			return;
		ExecuteSound(m_Pending[m_Head].soundName, lock, m_Pending[m_Head].volume);
		m_Head = (m_Head + 1) % MAX_PENDING;
	}

}

void dae::SDLSoundSystem::PlayMusic(const std::string& soundName)
{
	if(m_MusicMap.contains(soundName))
		Mix_PlayMusic(m_MusicMap[soundName]->GetMusic(), -1);
	else
	{
		std::string copy{soundName};
		m_MusicMap.insert(std::make_pair(copy, ResourceManager::GetInstance().LoadMusic(soundName)));
		if(Mix_PlayMusic(m_MusicMap[soundName]->GetMusic(), -1) == -1)
		{
			std::cout << "Could not Play music\n";
		}
	}
}

void dae::SDLSoundSystem::MuteSoundSystem()
{
	std::lock_guard lock{m_MuteMutex};
	if(!m_IsMuted)
	{
		Mix_Volume(-1, 0);
		Mix_VolumeMusic(0);
		m_IsMuted = true;
	}

}

void dae::SDLSoundSystem::ExecuteSound(std::string soundName, std::unique_lock<std::mutex>& lock, int volume)
{

	if(m_SoundMap.contains(soundName))
	{
		lock.unlock();
		m_SoundMap[soundName]->PlaySoundEffect(volume);
		lock.lock();
	}
	else
	{
		std::string name = soundName;
		auto        entry{std::make_pair<std::string, std::unique_ptr<const SoundEffect>>(
			std::move(name), ResourceManager::GetInstance().LoadSound(soundName))};
		m_SoundMap.insert(std::move(entry));
		lock.unlock();
		m_SoundMap[soundName]->PlaySoundEffect(volume);
		lock.lock();
	}
}

dae::SDLSoundSystem::SDLSoundSystem()
{
	if(Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		std::cout << "SDL2_Mixer could not be initialized!\n";
		return;
	}
	m_AudioThread = std::thread{&SDLSoundSystem::Update, this};
}
