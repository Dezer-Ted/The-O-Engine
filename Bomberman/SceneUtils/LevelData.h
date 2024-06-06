#pragma once

struct LevelData final {
	int   m_NumberOfEnemies{};
	int   m_NumberOfPowerUps{};
	float m_WallFillAmount{};
	int   m_EnemyTypes[4];
};
