#pragma once
#include <string>

#include "../DesignPatterns/Singleton.h"

namespace dae
{
	class SoundSystem {
	public:
		virtual      ~SoundSystem() = default;
		virtual void Play(const std::string& soundName, int volume = 64) = 0;
	};

	class DefaultSoundSystem final : public SoundSystem {
	public:
		DefaultSoundSystem() = default;
		DefaultSoundSystem(const DefaultSoundSystem& other) = delete;
		DefaultSoundSystem(DefaultSoundSystem&& other) noexcept = delete;
		DefaultSoundSystem& operator=(const DefaultSoundSystem& other) = delete;
		DefaultSoundSystem& operator=(DefaultSoundSystem&& other) noexcept = delete;
		virtual             ~DefaultSoundSystem() override = default;

	private:
		virtual void Play(const std::string&, int = 64) override
		{
		}
	};
}
