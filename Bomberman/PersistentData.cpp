#include "PersistentData.h"


void dae::PersistentData::UpdateUpgrades(const UpgradeDataHolder& UpgradeData, const std::string& key)
{
	m_UpgradeNameMap[key] = UpgradeData;
}

dae::UpgradeDataHolder dae::PersistentData::GetUpgradeData(const std::string& key) const
{
	return m_UpgradeNameMap.at(key);
}

bool dae::PersistentData::CheckIfKeyExists(const std::string& key) const
{
	return m_UpgradeNameMap.contains(key);
}

void dae::PersistentData::PlayerDied()
{
	if(m_PlayerDied)
		return;
	m_PlayerDied = true;
	--m_PlayerLifes;
}

void dae::PersistentData::SetScore(int score)
{
	m_Score = score;
}

int dae::PersistentData::GetScore() const
{
	return m_Score;
}

int dae::PersistentData::GetLifes() const
{
	return m_PlayerLifes;
}

void dae::PersistentData::RenableLives()
{
	m_PlayerDied = false;
}
