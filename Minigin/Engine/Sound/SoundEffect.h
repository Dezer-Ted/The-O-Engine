#pragma once
#include <SDL_mixer.h>

namespace dae
{
	class SoundEffect final {
	public:
		SoundEffect(Mix_Chunk* soundChunk);
		SoundEffect(const SoundEffect& other) = delete;
		SoundEffect(SoundEffect&& other) noexcept = delete;
		SoundEffect& operator=(const SoundEffect& other) = delete;
		SoundEffect& operator=(SoundEffect&& other) noexcept = delete;
		~SoundEffect();
		void PlaySoundEffect(int volume) const;
	private:
		Mix_Chunk* m_SoundChunk{nullptr};
	};
}
