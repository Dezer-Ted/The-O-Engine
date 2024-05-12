#pragma once
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "Components/BaseComponent.h"


namespace dae
{
	class GridComponent;
	class Scene;

	class BombComponent final : public dae::BaseComponent {
	public:
		BombComponent(dae::GameObject* pOwner);
		BombComponent(const BombComponent& other) = delete;
		BombComponent(BombComponent&& other) noexcept = delete;
		BombComponent& operator=(const BombComponent& other) = delete;
		BombComponent& operator=(BombComponent&& other) noexcept = delete;
		~BombComponent() override;
		void Update() override;
		void SetExplosionRange(int range);
		void Init(GridComponent* pGrid, const glm::vec2& gridPos);

	private:
		void           Explode() const;
		void           CreateExplosion() const;
		GameObject*    CreateExplosionCenter(Scene* scene, const glm::vec3& pos, float scale) const;
		void           CreateMidPiece(dae::Scene* scene, float scale, dae::GameObject* pParent, std::vector<int> directions, size_t i) const;
		void           CreateExplosionArms(Scene* scene, const glm::vec3& pos, float scale, GameObject* pParent) const;
		const float    m_FuseTime{2.f};
		float          m_CurrentTimer{0.f};
		int            m_ExplosionRange{};
		GridComponent* m_pGrid{nullptr};
		glm::vec2      m_GridPos{};
	};
}
