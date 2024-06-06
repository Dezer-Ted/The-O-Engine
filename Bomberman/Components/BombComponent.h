#pragma once
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "../GridComponent.h"
#include "Components/BaseComponent.h"
#include "Engine/DesignPatterns/Observer.h"


namespace dae
{
	class PlayerComponent;
	class GridComponent;
	class Scene;

	class BombComponent final : public dae::BaseComponent, public Observable, public Observer {
	public:
		BombComponent(dae::GameObject* pOwner);
		BombComponent(const BombComponent& other) = delete;
		BombComponent(BombComponent&& other) noexcept = delete;
		BombComponent& operator=(const BombComponent& other) = delete;
		BombComponent& operator=(BombComponent&& other) noexcept = delete;
		~BombComponent() override;
		void Update() override;
		void SetExplosionRange(int range);
		void Init(GridComponent* pGrid, const CellCoordinate& gridPos, PlayerComponent* pPlayer);
		void Explode() const;

		void Notify(Utils::GameEvent event, ObserverEventData* eventData) override;

	private:
		void        CreateExplosion() const;
		GameObject* CreateExplosionCenter(Scene* scene, const glm::vec3& pos, float scale) const;
		void        CreateMidPiece(dae::Scene* scene, float scale, dae::GameObject* pParent, std::vector<int> directions, size_t i) const;
		void        CreateExplosionArms(Scene* scene, float scale, GameObject* pParent) const;


		const float      m_FuseTime{2.f};
		float            m_CurrentTimer{0.f};
		int              m_ExplosionRange{};
		GridComponent*   m_pGrid{nullptr};
		CellCoordinate   m_GridPos{};
		PlayerComponent* m_pPLayer{nullptr};
	};
}
