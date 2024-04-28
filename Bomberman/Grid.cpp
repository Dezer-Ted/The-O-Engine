#include "Grid.h"

#include "Components/ColliderComponent.h"
#include "Components/SpriteComponent.h"
#include "SceneObjects/GameObject.h"


dae::Grid::Grid(int mapSizeX, int mapSizeY, int xCellCount, int yCellCount)
{
	m_CellWidth = mapSizeX / xCellCount;
	m_CellHeight = mapSizeY / yCellCount;
	m_Grid.resize(yCellCount);
	for(int i = 0; i < yCellCount; ++i)
	{
		m_Grid[i].reserve(xCellCount);
		for(int j = 0; j < xCellCount; ++j)
		{
			if((i % 2 == 0 && j % 2 == 0) || (i == 0 || i == yCellCount - 1 || j == 0 || j == xCellCount - 1))
				m_Grid[i].emplace_back(glm::vec2{j * m_CellWidth, i * m_CellHeight}, WallState::BorderWall);
			else
				m_Grid[i].emplace_back(glm::vec2{j * m_CellWidth, i * m_CellHeight}, WallState::open);
		}
	}

}

void dae::Grid::CreateBorderWall(dae::Scene& scene, std::vector<dae::Cell>::value_type& cell)
{
	auto go = std::make_shared<GameObject>(&scene);
	go->SetPosition(cell.m_Position.x, cell.m_Position.y);
	go->SetTag("Wall");
	auto spriteComp = go->AddComponent<SpriteComponent>();
	spriteComp->AddSprite(1, 1, "Obstacles/BorderWall.png", "BaseSprite");
	spriteComp->ShouldUpdate(false);
	spriteComp->SetScale(3.f);
	auto collisionComp = go->AddComponent<ColliderComponent>();
	collisionComp->AdjustBoundsToSpriteSize();
	scene.Add(go);
}

void dae::Grid::InitWalls(Scene& scene)
{
	for(auto& row : m_Grid)
	{
		for(auto& cell : row)
		{
			switch(cell.m_WallState)
			{
			case WallState::BorderWall:
				CreateBorderWall(scene, cell);
				break;
			case WallState::Wall:
				break;
			case WallState::open:
				break;
			}
		}
	}
}

glm::vec2 dae::Grid::GetStartPosition() const
{
	return m_Grid[1][1].m_Position;
}

glm::vec2 dae::Grid::GetGridCellPosition(const glm::vec2& currentPos) const
{
	const int xIndex = static_cast<int>(currentPos.x / static_cast<float>(m_CellWidth));
	const int yIndex = static_cast<int>(currentPos.y / static_cast<float>(m_CellHeight));
	glm::vec2 center{m_Grid[yIndex][xIndex].m_Position};
	return center;
}
