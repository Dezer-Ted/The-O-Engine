#pragma once
#include <SDL_mixer.h>

class MusicTrack final {
public:
	MusicTrack(Mix_Music* pMusic);
	MusicTrack(const MusicTrack& other) = delete;
	MusicTrack(MusicTrack&& other) noexcept = delete;
	MusicTrack& operator=(const MusicTrack& other) = delete;
	MusicTrack& operator=(MusicTrack&& other) noexcept = delete;
	Mix_Music* GetMusic() const;
	~MusicTrack();
private:
	Mix_Music* m_pMusic{nullptr};
};
