﻿#include "PersistentData.h"


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
