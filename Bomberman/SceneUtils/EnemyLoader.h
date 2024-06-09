#pragma once
#include "../GridComponent.h"
#include "SceneObjects/GameObject.h"

namespace dae
{
	class EnemyLoader {
	public:
		static GameObject* LoadOneal(Scene* pScene, const std::vector<GameObject*>& players, GridComponent* pGrid, const glm::vec2& position);
		static GameObject* LoadBalloom(::dae::Scene* pScene, const glm::vec2& position);
		static GameObject* LoadDoll(::dae::Scene* pScene, const glm::vec2& position);
		static GameObject* LoadMinvo(Scene* pScene, const std::vector<GameObject*>& players, GridComponent* pGrid, const glm::vec2& position);
	};
}
