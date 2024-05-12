#pragma once
#include <vector>
#include <glm/vec2.hpp>

#include "Components/BaseComponent.h"
#include "EnemyStates/BaseState.h"
#include "EnemyStates/BaseState.h"
#include "SceneObjects/Scene.h"

namespace dae
{
	enum class WallState {
		BorderWall,
		Wall,
		open
	};

	struct Cell final {
		glm::vec2 m_Position;
		WallState m_WallState;
	};

	class GridComponent final : public BaseComponent {
	public:
		GridComponent(GameObject* pOwner);
		void InitGrid(int mapSizeX, int mapSizeY, int xCellCount, int yCellCount);
		void CreateBorderWall(dae::Scene& scene, std::vector<dae::Cell>::value_type& cell);
		GridComponent(const GridComponent& other) = delete;
		GridComponent(GridComponent&& other) noexcept = delete;
		GridComponent& operator=(const GridComponent& other) = delete;
		GridComponent& operator=(GridComponent&& other) noexcept = delete;
		~GridComponent() = default;
		void      InitWalls(Scene& scene);
		glm::vec2 GetPositionAtIndex(int x, int y) const;
		glm::vec2 GetGridCellPosition(const glm::vec2& currentPos) const;
		WallState GetWallstateAtPos(const glm::vec2& currentPos) const;
		glm::vec2 GetGridCoordinate(const glm::vec2& currentPos) const;
		int       GetCellWidth() const;
		int       GetCellHeight() const;

	private:
		std::vector<std::vector<Cell>> m_Grid;
		int                            m_CellWidth;
		int                            m_CellHeight;
	};
}
