#include "MusicTrack.h"

MusicTrack::MusicTrack(Mix_Music* pMusic)
{
	m_pMusic = pMusic;
}

Mix_Music* MusicTrack::GetMusic() const
{
	return m_pMusic;
}

MusicTrack::~MusicTrack()
{
	Mix_FreeMusic(m_pMusic);
}
