#include "MenuLoader.h"

#include <fstream>
#include <json.hpp>

#include "../HighScoreList.h"
#include "../Commands/MenuNavigateCommand.h"
#include "../Commands/MenuSelectCommand.h"
#include "../Components/MenuNavigatorComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/TextComponent.h"
#include "Engine/ResourceManager.h"
#include "Input/InputManager.h"
#include "SceneObjects/SceneManager.h"
#include "SceneObjects/GameObject.h"

void dae::MenuLoader::LoadLogo(dae::Scene* pScene)
{
	auto go{std::make_shared<dae::GameObject>(pScene)};
	auto spriteComp = go->AddComponent<dae::SpriteComponent>();
	spriteComp->AddSprite(1, 1, "Misc/BombermanLogo.png", "Logo");
	spriteComp->SetScale(2.f);
	spriteComp->ShouldUpdate(false);
	go->SetPosition(80, 20);
	go->AddToUI();
	pScene->Add(go);
}

void dae::MenuLoader::LoadModes(dae::Scene* pScene)
{
	const auto menuNavigator{std::make_shared<GameObject>(pScene)};
	menuNavigator->AddToUI();
	const auto navComp = menuNavigator->AddComponent<MenuNavigatorComponent>();
	menuNavigator->SetPosition(150, 325);
	const auto spriteComp = menuNavigator->AddComponent<SpriteComponent>();
	spriteComp->AddSprite(1, 1, "Misc/Indicator.png", "Indicator");
	spriteComp->ShouldUpdate(false);

	InputManager::GetInstance().AddControllerCompoundAction<MenuNavigateCommand>(
		dae::Controller::ButtonInputs::DPadUp,
		dae::Controller::ButtonInputs::DPadDown,
		dae::Controller::ButtonInputs::DPadLeft,
		dae::Controller::ButtonInputs::DPadRight,
		menuNavigator.get()
	);
	InputManager::GetInstance().AddControllerActionMapping<MenuSelectCommand>(ControllerAction::ActionType::ButtonMap, menuNavigator.get(),
	                                                                          Controller::ButtonInputs::AButton,
	                                                                          ControllerAction::InputType::ButtonDown);
	auto go{std::make_shared<GameObject>(pScene)};
	go->AddToUI();
	auto       textComp = go->AddComponent<TextComponent>();
	const auto font{ResourceManager::GetInstance().LoadFont("nes.otf", 20)};
	textComp->SetText("SinglePlayer", font, SDL_Color{255, 255, 255, 255});
	go->SetPosition(200, 325);
	navComp->RegisterMenuItem(go.get());
	pScene->Add(go);

	go = std::make_shared<GameObject>(pScene);
	go->AddToUI();
	textComp = go->AddComponent<TextComponent>();
	textComp->SetText("Versus", font, SDL_Color{255, 255, 255, 255});
	go->SetPosition(250, 375);
	navComp->RegisterMenuItem(go.get());
	pScene->Add(go);

	go = std::make_shared<GameObject>(pScene);
	go->AddToUI();
	textComp = go->AddComponent<TextComponent>();
	textComp->SetText("Coop", font, SDL_Color{255, 255, 255, 255});
	go->SetPosition(275, 425);
	navComp->RegisterMenuItem(go.get());
	pScene->Add(go);

	pScene->Add(menuNavigator);
}

void dae::MenuLoader::LoadHighScoreList(Scene* pScene)
{
	std::vector<HighscoreEntry> entries;
	entries.push_back(HighscoreEntry{0, "AAA"});
	entries.push_back(HighscoreEntry{0, "AAA"});
	entries.push_back(HighscoreEntry{0, "AAA"});
	entries.push_back(HighscoreEntry{0, "AAA"});
	entries.push_back(HighscoreEntry{0, "AAA"});
	entries.push_back(HighscoreEntry{0, "AAA"});
	entries.push_back(HighscoreEntry{0, "AAA"});
	entries.push_back(HighscoreEntry{0, "AAA"});
	entries.push_back(HighscoreEntry{0, "AAA"});
	entries.push_back(HighscoreEntry{0, "AAA"});
	entries.push_back(HighscoreEntry{0, "AAA"});
	nlohmann::json json{entries};
	std::ofstream  os{"../Data/scores.json"};
	os << json.dump();
	os.close();

}

void dae::MenuLoader::LoadStartScreen()
{
	auto pScene = dae::SceneManager::GetInstance().CreateScene("StartScreen");
	LoadLogo(pScene);
	LoadModes(pScene);

	SceneManager::GetInstance().LoadScene("StartScreen");

}

void dae::MenuLoader::LoadEndScreen()
{
	auto pScene = dae::SceneManager::GetInstance().CreateScene("EndScreen");
	LoadHighScoreList(pScene);
}
