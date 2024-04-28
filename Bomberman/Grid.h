#pragma once
#include <vector>
#include <glm/vec2.hpp>

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

	class Grid final {
	public:
		Grid(int mapSizeX, int mapSizeY, int xCellCount, int yCellCount);
		void CreateBorderWall(dae::Scene& scene, std::vector<dae::Cell>::value_type& cell);
		Grid(const Grid& other) = delete;
		Grid(Grid&& other) noexcept = delete;
		Grid& operator=(const Grid& other) = delete;
		Grid& operator=(Grid&& other) noexcept = delete;
		~Grid() = default;
		void InitWalls(Scene& scene);
		glm::vec2 GetStartPosition()const;
		glm::vec2 GetGridCellPosition(const glm::vec2& currentPos ) const;
	private:
		std::vector<std::vector<Cell>> m_Grid;
		int m_CellWidth;
		int m_CellHeight;
	};
}
