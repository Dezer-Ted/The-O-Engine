#pragma once
#include <memory>
#include <SDL_mixer.h>
#include <unordered_map>
#include <mutex>

#include "MusicTrack.h"
#include "SoundEffect.h"
#include "SoundSystem.h"

namespace dae
{
	struct PlayMessage {
		std::string soundName;
		int         volume;
	};

	class SDLSoundSystem final : public SoundSystem {
	public:
		SDLSoundSystem();
		SDLSoundSystem(const SDLSoundSystem& other) = delete;
		SDLSoundSystem(SDLSoundSystem&& other) noexcept = delete;
		SDLSoundSystem& operator=(const SDLSoundSystem& other) = delete;
		SDLSoundSystem& operator=(SDLSoundSystem&& other) noexcept = delete;
		~SDLSoundSystem() override;
		void Play(const std::string& soundName, int volume) override;
		void Update();
		void PlayMusic(const std::string& soundName) override;
		void MuteSoundSystem() override;

	private:
		void ExecuteSound(std::string soundName, std::unique_lock<std::mutex>& lock, int volume = 64);


		std::unordered_map<std::string, const std::unique_ptr<const SoundEffect>> m_SoundMap;
		std::unordered_map<std::string, const std::unique_ptr<const MusicTrack>>  m_MusicMap;
		friend class Singleton<SDLSoundSystem>;
		static const int        MAX_PENDING{16};
		PlayMessage             m_Pending[MAX_PENDING];
		int                     m_NumPending{};
		int                     m_Head{};
		int                     m_Tail{};
		std::mutex              m_QueueMutex{};
		std::condition_variable m_Queue{};
		std::mutex              m_MuteMutex{};
		std::thread             m_AudioThread;
		bool                    m_IsRunning = true;
		bool                    m_IsMuted{false};
	};
}
