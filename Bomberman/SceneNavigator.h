#pragma once

namespace dae
{
	class SceneNavigator final {
	public:
		static void UnloadStage();
		static void LoadStage();
		static void ReloadStage();

		inline static bool m_LevelCompleted{false};

	private:
		inline static bool m_IsUnloaded{false};
		inline static int  m_LevelIndex{0};
	};
}
