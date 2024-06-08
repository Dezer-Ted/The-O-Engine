#pragma once
#include <json.hpp>
#include <string>
#include <vector>

namespace dae
{
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

	class HighScoreList final {
	public:
		HighScoreList();
		HighScoreList(const HighScoreList& other) = delete;
		HighScoreList(HighScoreList&& other) noexcept = delete;
		HighScoreList& operator=(const HighScoreList& other) = delete;
		HighScoreList& operator=(HighScoreList&& other) noexcept = delete;
		~HighScoreList() = default;

	private:
		std::vector<HighscoreEntry> m_Highscores;
	};
}
