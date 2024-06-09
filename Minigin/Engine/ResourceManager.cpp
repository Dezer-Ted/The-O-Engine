#include <stdexcept>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "ResourceManager.h"

#include <iostream>

#include "../Rendering/Renderer.h"
#include "../Rendering/Texture2D.h"
#include "../Rendering/Font.h"
#include "fstream"
#include "../../3rdParty/nlohmann/json.hpp"

void dae::ResourceManager::Init(const std::string& dataPath)
{
	m_dataPath = dataPath;

	if(TTF_Init() != 0)
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

std::shared_ptr<dae::Texture2D> dae::ResourceManager::LoadTexture(const std::string& file) const
{
	const auto fullPath = m_dataPath + file;
	auto       texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if(texture == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}
	return std::make_shared<Texture2D>(texture);
}

std::shared_ptr<dae::Font> dae::ResourceManager::LoadFont(const std::string& file, unsigned int size) const
{
	return std::make_shared<Font>(m_dataPath + file, size);
}

std::unique_ptr<dae::SoundEffect> dae::ResourceManager::LoadSound(const std::string& file) const
{
	std::string fullFile{m_dataPath + "Sound/" + file + ".wav"};
	return std::make_unique<SoundEffect>(Mix_LoadWAV(fullFile.c_str()));
}

std::unique_ptr<MusicTrack> dae::ResourceManager::LoadMusic(const std::string& file) const
{
	std::string fullFile{m_dataPath + "Sound/" + file + ".wav"};
	return std::make_unique<MusicTrack>(Mix_LoadMUS(fullFile.c_str()));
}

std::string dae::ResourceManager::LoadJson(const std::string& file) const
{
	std::string   fullPath{m_dataPath + file};
	std::ifstream fileStream{fullPath};
	if(!fileStream.is_open())
	{
		std::cerr << "Failed to open file: " << fullPath << "\n";
		return "";
	}
	std::string json;
	std::string line;
	while(std::getline(fileStream, line))
	{
		json += line;
	}
	fileStream.close();
	return json;
}
