#pragma once
#include <memory>
#include <SDL_mixer.h>
#include <unordered_map>

#include "SoundEffect.h"
#include "SoundSystem.h"

namespace dae
{
	class SDLSoundSystem final : public SoundSystem, public Singleton<SDLSoundSystem> {
	public:
		SDLSoundSystem(const SDLSoundSystem& other) = delete;
		SDLSoundSystem(SDLSoundSystem&& other) noexcept = delete;
		SDLSoundSystem& operator=(const SDLSoundSystem& other) = delete;
		SDLSoundSystem& operator=(SDLSoundSystem&& other) noexcept = delete;
		~SDLSoundSystem() override;
		void Play(const std::string& soundName, int volume) override;

	private:
		SDLSoundSystem();
		std::unordered_map<std::string, std::unique_ptr<SoundEffect>> m_SoundMap;
		friend class Singleton<SDLSoundSystem>;
	};
}
