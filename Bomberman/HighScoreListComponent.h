#pragma once
#include <json.hpp>
#include <string>
#include <vector>

#include "Components/BaseComponent.h"


namespace dae
{
	class Scene;
	class TextComponent;

	struct HighscoreEntry {
		int         m_Score;
		std::string m_Name;
		
	};

	inline void to_json(nlohmann::json& json, const HighscoreEntry& entry)
	{
		json = nlohmann::json{
			{"score", entry.m_Score},
			{"name", entry.m_Name}
		};
	}

	inline void from_json(const nlohmann::json& json, HighscoreEntry& entry)
	{
		entry.m_Score = json.at("score").get<int>();
		entry.m_Name = json.at("name").get<std::string>();
	}

	class HighScoreListComponent final : public BaseComponent {
	public:
		HighScoreListComponent(GameObject* pParent);
		HighScoreListComponent(const HighScoreListComponent& other) = delete;
		HighScoreListComponent(HighScoreListComponent&& other) noexcept = delete;
		HighScoreListComponent& operator=(const HighScoreListComponent& other) = delete;
		HighScoreListComponent& operator=(HighScoreListComponent&& other) noexcept = delete;
		~HighScoreListComponent() override = default;
		void                        LoadScoresFromDisc();
		std::vector<HighscoreEntry> DeserializeHighscores(const nlohmann::json& j);
		void                        CreateListGameObjects(Scene* pScene);
		void                        AddScore(const HighscoreEntry& entry);

	private:
		void                                                   SortHighscores();
		void                                                   UpdateScores() const;
		void WriteScoresToJson();
		
		std::vector<HighscoreEntry>                            m_Highscores;
		std::vector<std::pair<TextComponent*, TextComponent*>> m_HighscoreObjects;
	};
}
