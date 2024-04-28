#pragma once
#include <memory>

#include "SDLSoundSystem.h"
#include "SoundSystem.h"

namespace dae
{
	class DebugSoundSystem final : public dae::SoundSystem {
	public:
		DebugSoundSystem(std::unique_ptr<SoundSystem>&& realSoundSystem);
		DebugSoundSystem(const DebugSoundSystem& other) = delete;
		DebugSoundSystem(DebugSoundSystem&& other) noexcept = delete;
		DebugSoundSystem& operator=(const DebugSoundSystem& other) = delete;
		DebugSoundSystem& operator=(DebugSoundSystem&& other) noexcept = delete;

		void Play(const std::string& soundName, int volume) override;

	private:
		std::unique_ptr<SoundSystem> m_SoundSystem;
	};
}
