#pragma once
#include <vector>
#include <glm/vec2.hpp>

#include "Components/BaseComponent.h"
#include "EnemyStates/BaseState.h"
#include "EnemyStates/BaseState.h"
#include "EnemyStates/BaseState.h"
#include "EnemyStates/BaseState.h"
#include "EnemyStates\BaseState.h"
#include "EnemyStates\BaseState.h"
#include "SceneObjects/Scene.h"

namespace dae
{
	enum class WallState {
		BorderWall,
		Barrier,
		Wall,
		open
	};

	struct Cell final {
		glm::vec2   m_Position;
		WallState   m_WallState;
		GameObject* m_CellObject;
	};

	struct CellCoordinate final {
		int x;
		int y;
	};

	class GridComponent final : public BaseComponent {
	public:
		GridComponent(GameObject* pOwner);
		void InitGrid(int mapSizeX, int mapSizeY, int xCellCount, int yCellCount);
		GridComponent(const GridComponent& other) = delete;
		GridComponent(GridComponent&& other) noexcept = delete;
		GridComponent& operator=(const GridComponent& other) = delete;
		GridComponent& operator=(GridComponent&& other) noexcept = delete;
		~GridComponent() override = default;

		void                  CreateWallObjects(Scene& scene, float fillAmount);
		glm::vec2             GetPositionAtIndex(int x, int y) const;
		glm::vec2             GetGridCellPosition(const CellCoordinate& currentPos) const;
		WallState             GetWallstateAtPos(const CellCoordinate& currentPos) const;
		::dae::CellCoordinate GetGridCoordinate(const glm::vec2& currentPos) const;
		int                   GetCellWidth() const;
		int                   GetCellHeight() const;
		GameObject*           GetCellObject(const CellCoordinate& currentPos) const;
		void                  MarkAsDestroyed(const CellCoordinate& currentPos);
		glm::vec2             GetRandomOpenCellPosition();
		void                  GenerateUpgrades(int amount);

	private:
		void CreateBorderWall(dae::Scene& scene, Cell& cell);
		void CreateWall(Scene& scene, Cell& cell);
		void InitWalls();

		std::vector<std::vector<Cell>> m_Grid;
		int                            m_CellWidth;
		int                            m_CellHeight;
		float                          m_FillPercentage{0.1f};
	};
}
