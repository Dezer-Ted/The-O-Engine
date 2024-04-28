#include "SoundEffect.h"

#include <iostream>

dae::SoundEffect::SoundEffect(Mix_Chunk* soundChunk)
	: m_SoundChunk(soundChunk)
{

}

dae::SoundEffect::~SoundEffect()
{
	Mix_FreeChunk(m_SoundChunk);
}

void dae::SoundEffect::PlaySoundEffect(int volume) const
{
	Mix_VolumeChunk(m_SoundChunk, volume);
	if(Mix_PlayChannel(-1, m_SoundChunk, 0) == -1)
	{
		std::cout << "FailedToPlaySoundEffect\n";
	}
}
