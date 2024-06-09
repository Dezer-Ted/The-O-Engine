#include "LevelLoader.h"

#include <fstream>
#include <SDL_rect.h>

#include "EnemyLoader.h"
#include "LevelData.h"
#include "PlayerLoader.h"
#include "Engine/DesignPatterns/ServiceLocator.h"
#include "Engine/Sound/DebugSoundSystem.h"
#include "SceneObjects/SceneManager.h"
#include "../GridComponent.h"
#include "../Components/EnemyComponent.h"
#include "Rendering/Renderer.h"
#include "SceneObjects/GameObject.h"
#include "json.hpp"
#include "../PersistentData.h"
#include "../SceneNavigator.h"
#include "../Commands/MuteCommand.h"
#include "../Commands/SkipLevelCommand.h"
#include "../Components/ScoreComponent.h"
#include "../Components/VersusPlayerComponent.h"
#include "Components/CameraComponent.h"
#include "Components/TextComponent.h"
#include "Engine/ResourceManager.h"
#include "Input/InputManager.h"

void dae::LevelLoader::LoadLevel(const std::string& levelPath)
{
	LevelData   levelData{LoadLevelFromJson(levelPath)};
	std::string levelName{levelPath.substr(levelPath.find('/') + 1)};
	levelName = levelName.substr(0, levelName.find('.'));
	auto                     scene = dae::SceneManager::GetInstance().CreateScene(levelName);
	SDL_Rect                 levelBounds{0, 0, 1395, 624};
	auto                     gridComp{InitGrid(scene, levelBounds, levelData.m_NumberOfPowerUps, levelData.m_WallFillAmount)};
	std::vector<GameObject*> players;
	auto                     pPlayer = dae::PlayerLoader::LoadPlayer(scene, levelBounds, gridComp, "Player1");
	players.push_back(pPlayer);
	if(m_GameMode == GameMode::Versus)
	{
		auto otherPlayer = dae::PlayerLoader::LoadVersusPlayer(scene, levelBounds, gridComp);
		auto camComp{pPlayer->GetComponentByClass<CameraComponent>()};
		camComp->SetAdditionalTarget(otherPlayer);
		otherPlayer->GetComponentByClass<VersusPlayerComponent>()->AddObserver(camComp);

	}
	else if(m_GameMode == GameMode::Coop)
	{
		auto otherPlayer = dae::PlayerLoader::LoadCoopPlayer(scene, levelBounds, gridComp, "Player2");
		pPlayer->GetComponentByClass<CameraComponent>()->SetAdditionalTarget(otherPlayer);
		glm::vec2 player1Pos{gridComp->GetGridCellPosition(CellCoordinate{1, 2})};
		glm::vec2 player2Pos{gridComp->GetGridCellPosition(CellCoordinate{2, 1})};
		pPlayer->SetPosition(player1Pos.x, player2Pos.y);
		otherPlayer->SetPosition(player2Pos.x, player2Pos.y);
		players.push_back(otherPlayer);
	}
	auto go = std::make_shared<GameObject>(scene);
	InputManager::GetInstance().AddKeyBoardActionMapping<SkipLevelCommand>(KeyboardAction::ActionType::ButtonMap,
	                                                                       KeyboardAction::InputType::OnButtonUp, go.get(), SDL_SCANCODE_F1);
	scene->Add(go);
	go = std::make_shared<GameObject>(scene);
	auto textComp = go->AddComponent<TextComponent>();
	auto font = ResourceManager::GetInstance().LoadFont("nes.otf", 20);
	textComp->SetText("0", font, SDL_Color{0, 0, 0, 255});
	go->SetPosition(500, 20);
	go->AddComponent<ScoreComponent>();
	go->AddToUI();
	scene->Add(go);
	go = std::make_shared<GameObject>(scene);
	textComp = go->AddComponent<TextComponent>();
	textComp->SetText("Lives Left " + std::to_string(PersistentData::GetInstance().GetLifes()), font, SDL_Color{0, 0, 0, 255});
	go->AddToUI();
	go->SetPosition(20, 20);
	scene->Add(go);
	InitEnemies(scene, players, levelData, gridComp);
	go = std::make_shared<GameObject>(scene);
	InputManager::GetInstance().AddKeyBoardActionMapping<MuteCommand>(KeyboardAction::ActionType::ButtonMap, KeyboardAction::InputType::OnButtonUp,
	                                                                  go.get(), SDL_SCANCODE_F2);
	scene->Add(go);
	dae::SceneManager::GetInstance().LoadScene(levelName);
	dae::Renderer::GetInstance().SetBackgroundColor(SDL_Color{57, 132, 0, 1});
	ServiceLocator::GetSoundSystem()->PlayMusic("MainTheme");
}

LevelData dae::LevelLoader::LoadLevelFromJson(const std::string levelPath)
{
	std::string data = ResourceManager::GetInstance().LoadJson(levelPath);
	auto        parsedData = nlohmann::json::parse(data);
	LevelData   level{};
	parsedData.at("EnemyTypes").get_to(level.m_EnemyTypes);
	parsedData.at("NumberOfEnemies").get_to(level.m_NumberOfEnemies);
	parsedData.at("NumberOfUpgrades").get_to(level.m_NumberOfPowerUps);
	parsedData.at("WallFillAmount").get_to(level.m_WallFillAmount);
	return level;
}

dae::GridComponent* dae::LevelLoader::InitGrid(Scene* pScene, const SDL_Rect& bounds, int itemAmount, float fillAmount)
{
	auto go{std::make_shared<GameObject>(pScene)};
	auto gridComp = go->AddComponent<dae::GridComponent>();
	gridComp->InitGrid(bounds.w, bounds.h, 31, 13);
	gridComp->CreateWallObjects(*pScene, fillAmount);
	gridComp->GenerateUpgrades(itemAmount);
	gridComp->GenerateExit();
	pScene->Add(go);
	return gridComp;
}

void dae::LevelLoader::InitEnemies(Scene* pScene, const std::vector<GameObject*>& players, const LevelData& levelData, dae::GridComponent* gridComp)
{
	std::vector<EnemyType> enabledTypes;
	for(int i = 0; i < 4; ++i)
	{
		if(levelData.m_EnemyTypes[i] == 0)
			continue;
		enabledTypes.push_back(static_cast<EnemyType>(i));
	}
	for(int i = 0; i < levelData.m_NumberOfEnemies; ++i)
	{
		EnemyType type = enabledTypes[rand() % enabledTypes.size()];
		switch(type)
		{
		case EnemyType::Balloom:
			EnemyLoader::LoadBalloom(pScene, gridComp->GetRandomOpenCellPosition());
			break;
		case EnemyType::Oneal:
			EnemyLoader::LoadOneal(pScene, players, gridComp, gridComp->GetRandomOpenCellPosition());
			break;
		case EnemyType::Doll:
			EnemyLoader::LoadDoll(pScene, gridComp->GetRandomOpenCellPosition());
			break;
		case EnemyType::Minvo:
			EnemyLoader::LoadMinvo(pScene, players, gridComp, gridComp->GetRandomOpenCellPosition());
			break;
		}
	}
}
