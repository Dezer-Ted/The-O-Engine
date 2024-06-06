#pragma once
#include <string>
#include <memory>
#include <SDL_mixer.h>

#include "DesignPatterns/Singleton.h"
#include "Sound/SoundEffect.h"

namespace dae
{
	class Texture2D;
	class Font;

	class ResourceManager final : public Singleton<ResourceManager> {
	public:
		void                         Init(const std::string& data);
		std::shared_ptr<Texture2D>   LoadTexture(const std::string& file) const;
		std::shared_ptr<Font>        LoadFont(const std::string& file, unsigned int size) const;
		std::unique_ptr<SoundEffect> LoadSound(const std::string& file) const;
		std::string LoadJson(const std::string& file) const;

	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		std::string m_dataPath;
	};
}
