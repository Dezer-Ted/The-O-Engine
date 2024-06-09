#include "MenuLoader.h"

#include <json.hpp>
#include "../HighScoreListComponent.h"
#include "../PersistentData.h"
#include "../Commands/MenuNavigateCommand.h"
#include "../Commands/MenuSelectCommand.h"
#include "../Commands/NameSelectionAction.h"
#include "../Commands/SaveScoreCommand.h"
#include "../Components/CharacterScrollComponent.h"
#include "../Components/MenuNavigatorComponent.h"
#include "../Components/NameSelectionComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/TextComponent.h"
#include "Engine/ResourceManager.h"
#include "Input/InputManager.h"
#include "SceneObjects/SceneManager.h"
#include "SceneObjects/GameObject.h"
#include "../Commands/SkipLevelCommand.h"
#include "Engine/DesignPatterns/ServiceLocator.h"
#include "Rendering/Renderer.h"
#include "../Commands/MuteCommand.h"

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


void dae::MenuLoader::CreateNameSelection(Scene* pScene)
{
	const float height{350};
	float       leftStart{250};
	const auto  font{ResourceManager::GetInstance().LoadFont("nes.otf", 30)};
	auto        go{std::make_shared<GameObject>(pScene)};
	auto        listComp = go->AddComponent<HighScoreListComponent>();
	listComp->LoadScoresFromDisc();
	listComp->CreateListGameObjects(pScene);
	pScene->Add(go);
	auto nameSelector{std::make_shared<GameObject>(pScene)};
	auto nameSelComp = nameSelector->AddComponent<NameSelectionComponent>();
	nameSelComp->SetHighscoreListComp(listComp);
	auto downIndi{std::make_shared<GameObject>(pScene)};
	downIndi->AddToUI();
	auto spriteComp = downIndi->AddComponent<SpriteComponent>();
	spriteComp->AddSprite(1, 1, "Misc/DownIndicator.png", "Indicator");
	downIndi->SetPosition(leftStart + 5, height + 30);

	auto upIndi{std::make_shared<GameObject>(pScene)};
	upIndi->AddToUI();
	spriteComp = upIndi->AddComponent<SpriteComponent>();
	spriteComp->AddSprite(1, 1, "Misc/UpIndicator.png", "Indicator");
	upIndi->SetPosition(leftStart + 5, height - 15);
	nameSelComp->RegisterIndicators(upIndi.get(), downIndi.get());
	pScene->Add(upIndi);
	pScene->Add(downIndi);

	for(int i = 0; i < 3; ++i)
	{
		auto charObject{std::make_shared<GameObject>(pScene)};
		charObject->AddToUI();
		const auto textComp = charObject->AddComponent<TextComponent>();
		textComp->SetText("A", font, SDL_Color{255, 255, 255, 255});
		charObject->SetPosition(leftStart, height);
		const auto scrollComp = charObject->AddComponent<CharacterScrollComponent>();
		nameSelComp->RegisterCharacter(scrollComp);
		pScene->Add(charObject);
		leftStart += 40;
	}

	InputManager::GetInstance().AddControllerCompoundAction<NameSelectionAction>(
		dae::Controller::ButtonInputs::DPadUp,
		dae::Controller::ButtonInputs::DPadDown,
		dae::Controller::ButtonInputs::DPadLeft,
		dae::Controller::ButtonInputs::DPadRight,
		nameSelector.get()
	);
	InputManager::GetInstance().AddControllerActionMapping<SaveScoreCommand>(ControllerAction::ActionType::ButtonMap, nameSelector.get(),
	                                                                         Controller::ButtonInputs::AButton, ControllerAction::InputType::ButtonDown);
	go = std::make_shared<GameObject>(pScene);
	go->AddToUI();
	go->SetPosition(leftStart + 40, height);
	auto textComp = go->AddComponent<TextComponent>();
	textComp->SetText(std::to_string(PersistentData::GetInstance().GetScore()), font, SDL_Color{255, 255, 255, 255});
	pScene->Add(go);
	pScene->Add(nameSelector);
}

void dae::MenuLoader::LoadStartScreen()
{
	auto pScene = dae::SceneManager::GetInstance().CreateScene("StartScreen");
	LoadLogo(pScene);
	LoadModes(pScene);

	auto go{std::make_shared<GameObject>(pScene)};
	InputManager::GetInstance().AddKeyBoardActionMapping<MuteCommand>(KeyboardAction::ActionType::ButtonMap, KeyboardAction::InputType::OnButtonUp,
	                                                                  go.get(), SDL_SCANCODE_F2);
	pScene->Add(go);
	dae::ServiceLocator::GetSoundSystem()->PlayMusic("TitleTheme");
	SceneManager::GetInstance().LoadScene("StartScreen");

}

void dae::MenuLoader::LoadEndScreen()
{
	auto pScene = dae::SceneManager::GetInstance().CreateScene("EndScreen");
	CreateNameSelection(pScene);
	dae::ServiceLocator::GetSoundSystem()->PlayMusic("EndTheme");
	const auto font{ResourceManager::GetInstance().LoadFont("nes.otf", 20)};
	const auto fontSmall{ResourceManager::GetInstance().LoadFont("nes.otf", 15)};
	auto       go{std::make_shared<GameObject>(pScene)};
	go->AddToUI();
	go->SetPosition(180, 400);
	auto textComp = go->AddComponent<TextComponent>();
	textComp->SetText("Press A to Save", font, SDL_Color{255, 255, 255, 255});
	pScene->Add(go);
	go = std::make_shared<GameObject>(pScene);
	go->AddToUI();
	go->SetPosition(200, 430);
	textComp = go->AddComponent<TextComponent>();
	textComp->SetText("Press B to return", fontSmall, SDL_Color{255, 255, 255, 255});
	go = std::make_shared<GameObject>(pScene);
	InputManager::GetInstance().AddKeyBoardActionMapping<MuteCommand>(KeyboardAction::ActionType::ButtonMap, KeyboardAction::InputType::OnButtonUp,
	                                                                  go.get(), SDL_SCANCODE_F2);
	pScene->Add(go);
	InputManager::GetInstance().AddControllerActionMapping<SkipLevelCommand>(ControllerAction::ActionType::ButtonMap, go.get(),
	                                                                         Controller::ButtonInputs::BButton, ControllerAction::InputType::ButtonDown);
	pScene->Add(go);

	dae::Renderer::GetInstance().SetBackgroundColor(SDL_Color{0, 0, 0, 1});
	SceneManager::GetInstance().LoadScene("EndScreen");
}
