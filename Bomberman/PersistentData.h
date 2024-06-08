#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "Engine/DesignPatterns/Singleton.h"

namespace dae
{
	struct UpgradeDataHolder {
		int  m_FireUp;
		int  m_BombUp;
		bool m_Detonator;
	};

	class PersistentData final : public Singleton<PersistentData> {
	public:
		PersistentData(const PersistentData& other) = delete;
		PersistentData(PersistentData&& other) noexcept = delete;
		PersistentData& operator=(const PersistentData& other) = delete;
		PersistentData& operator=(PersistentData&& other) noexcept = delete;
		~PersistentData() override = default;
		void              UpdateUpgrades(const UpgradeDataHolder& UpgradeData, const std::string& key);
		UpgradeDataHolder GetUpgradeData(const std::string& key) const;
		bool              CheckIfKeyExists(const std::string& key) const;
		void              PlayerDied();
		void SetScore(int score);
		int GetScore() const;

	private:
		friend class Singleton<PersistentData>;
		PersistentData() = default;

		std::unordered_map<std::string, UpgradeDataHolder> m_UpgradeNameMap;
		int                                                m_PlayerLifes{3};
		int                                                m_Score{0};
	};
}
