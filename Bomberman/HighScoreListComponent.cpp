#include "HighScoreListComponent.h"

#include <fstream>

#include "Engine/ResourceManager.h"

#include "Components/TextComponent.h"
#include "SceneObjects/GameObject.h"
#include "SceneObjects/Scene.h"

dae::HighScoreListComponent::HighScoreListComponent(GameObject* pParent) : BaseComponent(pParent)
{
}

void dae::HighScoreListComponent::LoadScoresFromDisc()
{
	const std::string json{ResourceManager::GetInstance().LoadJson("scores.json")};
	auto              convertedJson{nlohmann::json::parse(json)};

	m_Highscores = DeserializeHighscores(convertedJson);
}

std::vector<dae::HighscoreEntry> dae::HighScoreListComponent::DeserializeHighscores(const nlohmann::json& j)
{
	std::vector<HighscoreEntry> entries;
	for(const auto& item : j)
	{
		for(const auto& subObject : item)
		{
			entries.push_back(subObject);
		}
	}
	return entries;
}

void dae::HighScoreListComponent::CreateListGameObjects(Scene* pScene)
{
	const auto  font{ResourceManager::GetInstance().LoadFont("nes.otf", 20)};
	float       startHeight{20};
	const float nameXPos{240};
	const float scoreXPos{340};
	for(const auto& entry : m_Highscores)
	{
		auto name{std::make_shared<GameObject>(pScene)};
		name->AddToUI();
		name->SetPosition(nameXPos, startHeight);
		auto nametextComp = name->AddComponent<TextComponent>();
		nametextComp->SetText(entry.m_Name, font, SDL_Color{255, 255, 255, 255});
		pScene->Add(name);
		auto score{std::make_shared<GameObject>(pScene)};
		score->AddToUI();
		score->SetPosition(scoreXPos, startHeight);
		auto scoretextComp = score->AddComponent<TextComponent>();
		scoretextComp->SetText(std::to_string(entry.m_Score), font, SDL_Color{255, 255, 255, 255});
		pScene->Add(score);
		startHeight += 25.f;
		m_HighscoreObjects.push_back(std::make_pair(nametextComp, scoretextComp));
	}
}

void dae::HighScoreListComponent::AddScore(const HighscoreEntry& entry)
{
	m_Highscores.push_back(entry);
	SortHighscores();
	UpdateScores();
	WriteScoresToJson();
}

void dae::HighScoreListComponent::SortHighscores()
{
	std::sort(m_Highscores.begin(), m_Highscores.end(), [](const HighscoreEntry& inputA, const HighscoreEntry& inputB)
	{
		return inputA.m_Score > inputB.m_Score;
	});
	m_Highscores.pop_back();
}

void dae::HighScoreListComponent::UpdateScores() const
{
	for(size_t i = 0; i < m_Highscores.size(); ++i)
	{
		m_HighscoreObjects[i].first->SetText(m_Highscores[i].m_Name);
		m_HighscoreObjects[i].second->SetText(std::to_string(m_Highscores[i].m_Score));
	}
}

void dae::HighScoreListComponent::WriteScoresToJson()
{

	nlohmann::json json{m_Highscores};
	std::ofstream  os{"../Data/scores.json", std::ios::trunc};
	os << json.dump();
	os.close();

}
