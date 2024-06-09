#include "GridComponent.h"

#include "Components/ColliderComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/WallComponent.h"
#include "SceneObjects/GameObject.h"


dae::GridComponent::GridComponent(GameObject* pOwner) : BaseComponent(pOwner)
{

}

void dae::GridComponent::InitGrid(int mapSizeX, int mapSizeY, int xCellCount, int yCellCount)
{
	m_CellWidth = mapSizeX / xCellCount;
	m_CellHeight = mapSizeY / yCellCount;
	m_Grid.resize(yCellCount);
	for(int i = 0; i < yCellCount; ++i)
	{
		m_Grid[i].reserve(xCellCount);
		for(int j = 0; j < xCellCount; ++j)
		{
			if(i == 0 || i == yCellCount - 1 || j == 0 || j == xCellCount - 1)
				m_Grid[i].emplace_back(glm::vec2{j * m_CellWidth, i * m_CellHeight}, WallState::BorderWall);
			else if((i % 2 == 0 && j % 2 == 0) || (i == 0 || i == yCellCount - 1 || j == 0 || j == xCellCount - 1))
				m_Grid[i].emplace_back(glm::vec2{j * m_CellWidth, i * m_CellHeight}, WallState::Barrier);
			else
				m_Grid[i].emplace_back(glm::vec2{j * m_CellWidth, i * m_CellHeight}, WallState::open);
		}
	}
}

void dae::GridComponent::CreateBorderWall(dae::Scene& scene, Cell& cell)
{
	auto go = std::make_shared<GameObject>(&scene);
	go->SetPosition(cell.m_Position.x, cell.m_Position.y);
	if(cell.m_WallState == WallState::BorderWall)
		go->SetTag("BorderWall");
	else
		go->SetTag("Barrier");
	go->SetLayer("Obstacle");
	auto spriteComp = go->AddComponent<SpriteComponent>();
	spriteComp->AddSprite(1, 1, "Obstacles/BorderWall.png", "BaseSprite");
	spriteComp->ShouldUpdate(false);
	spriteComp->SetScale(3.f);
	auto collisionComp = go->AddComponent<ColliderComponent>();
	collisionComp->AdjustBoundsToSpriteSize();
	scene.Add(go);
	cell.m_CellObject = go.get();
}

void dae::GridComponent::CreateWall(Scene& scene, Cell& cell)
{
	auto go = std::make_shared<GameObject>(&scene);
	go->SetPosition(cell.m_Position.x, cell.m_Position.y);
	go->SetTag("Wall");
	go->SetLayer("Obstacle");
	auto spriteComp = go->AddComponent<SpriteComponent>();
	spriteComp->AddSprite(6, 1, "Obstacles/WallCrumbling.png", "DestructionAnimation");
	spriteComp->AddSprite(1, 1, "Obstacles/Wall.png", "BaseSprite");
	spriteComp->ShouldUpdate(false);
	spriteComp->SetScale(3);
	auto collisionComp = go->AddComponent<ColliderComponent>();
	collisionComp->AdjustBoundsToSpriteSize();
	auto wallComp = go->AddComponent<WallComponent>();
	spriteComp->AddObserver(wallComp);
	scene.Add(go);
	cell.m_CellObject = go.get();
}

void dae::GridComponent::InitWalls()
{
	int amountOfCells = static_cast<int>(m_Grid.size() * m_Grid[0].size());
	int wallAmount = static_cast<int>(static_cast<float>(amountOfCells) * m_FillPercentage);
	for(int i{0}; i < wallAmount;)
	{
		int   randX{static_cast<int>(rand() % m_Grid[0].size())};
		int   randY{static_cast<int>(rand() % m_Grid.size())};
		Cell* currentCell = &m_Grid[randY][randX];
		if(currentCell->m_WallState != WallState::open || (randX <= 2 && randY <= 2))
			continue;
		currentCell->m_WallState = WallState::Wall;
		++i;
	}
}

void dae::GridComponent::GenerateUpgrades(int amount)
{
	std::vector<Cell*> wallCells;
	for(auto& row : m_Grid)
	{
		for(auto& cell : row)
		{
			if(cell.m_WallState == WallState::Wall)
				wallCells.push_back(&cell);
		}
	}
	for(int i = 0; i < amount;)
	{
		const int randomPowUp{rand() % 3};
		const int randomCell{static_cast<int>(rand() % wallCells.size())};
		auto      wallComp{wallCells[randomCell]->m_CellObject->GetComponentByClass<WallComponent>()};
		if(wallComp->HasPowerUp())
			continue;
		wallComp->SetPowerUp(static_cast<PowerUps>(randomPowUp));
		++i;
	}

}

void dae::GridComponent::GenerateExit()
{
	std::vector<Cell*> wallCells;
	for(auto& row : m_Grid)
	{
		for(auto& cell : row)
		{
			if(cell.m_WallState == WallState::Wall)
				wallCells.push_back(&cell);
		}
	}
	for(int i = 0; i < 1;)
	{
		int  randNum{static_cast<int>(rand() % wallCells.size())};
		auto wallComp{wallCells[randNum]->m_CellObject->GetComponentByClass<WallComponent>()};
		if(wallComp->HasPowerUp())
			continue;
		wallComp->SetExit();
		++i;
	}
}

void dae::GridComponent::CreateWallObjects(Scene& scene, float fillAmount)
{
	m_FillPercentage = fillAmount;
	InitWalls();
	for(auto& row : m_Grid)
	{
		for(auto& cell : row)
		{
			switch(cell.m_WallState)
			{
			case WallState::BorderWall:
			case WallState::Barrier:
				CreateBorderWall(scene, cell);
				break;
			case WallState::Wall:
				CreateWall(scene, cell);
				break;
			case WallState::open:
				break;
			}
		}
	}
}

glm::vec2 dae::GridComponent::GetPositionAtIndex(int x, int y) const
{
	return m_Grid[y][x].m_Position;
}

glm::vec2 dae::GridComponent::GetGridCellPosition(const dae::CellCoordinate& currentPos) const
{
	glm::vec2 center{m_Grid[currentPos.y][currentPos.x].m_Position};
	return center;
}

dae::WallState dae::GridComponent::GetWallstateAtPos(const dae::CellCoordinate& currentPos) const
{
	return m_Grid[currentPos.y][currentPos.x].m_WallState;
}

dae::CellCoordinate dae::GridComponent::GetGridCoordinate(const glm::vec2& currentPos) const
{
	const int xIndex = static_cast<int>((currentPos.x + static_cast<float>(m_CellWidth) / 4.f) / static_cast<float>(m_CellWidth));
	const int yIndex = static_cast<int>((currentPos.y + static_cast<float>(m_CellHeight) / 4.f) / static_cast<float>(m_CellHeight));
	return {xIndex, yIndex};
}

int dae::GridComponent::GetCellWidth() const
{
	return m_CellWidth;
}

int dae::GridComponent::GetCellHeight() const
{
	return m_CellHeight;
}

dae::GameObject* dae::GridComponent::GetCellObject(const dae::CellCoordinate& currentPos) const
{
	return m_Grid[currentPos.y][currentPos.x].m_CellObject;
}

void dae::GridComponent::MarkAsDestroyed(const dae::CellCoordinate& currentPos)
{
	m_Grid[currentPos.y][currentPos.x].m_WallState = WallState::open;
}

glm::vec2 dae::GridComponent::GetRandomOpenCellPosition()
{
	std::vector<Cell*> openCells;
	for(auto& row : m_Grid)
	{
		for(auto& cell : row)
		{
			if(cell.m_WallState != WallState::open)
				continue;
			openCells.push_back(&cell);
		}
	}
	int randomNum{static_cast<int>(rand() % openCells.size())};
	return openCells[randomNum]->m_Position;
}

glm::vec2 dae::GridComponent::GetRandomOpenCellPosition(int lowerBound, int upperBound)
{
	std::vector<Cell*> openCells;
	for(size_t i = lowerBound; i < upperBound; ++i)
	{
		for(size_t j = lowerBound; j < upperBound; ++j)
		{
			if(m_Grid[i][j].m_WallState != WallState::open)
				continue;
			openCells.push_back(&m_Grid[i][j]);
		}
	}
	int randomNum{static_cast<int>(rand() % openCells.size())};
	return openCells[randomNum]->m_Position;
}
