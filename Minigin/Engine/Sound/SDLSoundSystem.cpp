﻿#include "SDLSoundSystem.h"

#include <cassert>
#include <iostream>

#include "../ResourceManager.h"

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
			m_Pending[i].volume = std::max(volume, m_Pending[i].volume);
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
		ExecuteSound(m_Pending[m_Head].soundName, m_Pending[m_Head].volume);
		m_Head = (m_Head + 1) % MAX_PENDING;
	}

}

void dae::SDLSoundSystem::ExecuteSound(const std::string& soundName, int volume = 64)
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
	m_AudioThread = std::thread{&SDLSoundSystem::Update, this};
}
