#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <GameObject.h>
#include <Minigin.h>
#include <SceneManager.h>
#include <ResourceManager.h>
#include <Scene.h>
#include <GameObject.h>
#include <InputManager.h>
#include <Utils.h>
#include <Components/EncircleComponent.h>
#include <Components/FPSComponent.h>
#include <Components/MiscFunctionComponent.h>
#include <Components/TextComponent.h>
#include <Components/TextureComponent.h>
#include <Components/TrashTheCacheComponent.h>
#include <Command.h>
#include <Components/LifeDisplayComponent.h>
#include <Components/ScoreDisplayComponent.h>

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>();
	go->GetComponentByClass<dae::TextureComponent>()->SetTexture("background.tga");
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>();
	go->GetComponentByClass<dae::TextureComponent>()->SetTexture("logo.tga");

	go->SetPosition(216, 180);
	scene.Add(go);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextComponent>();
	go->SetPosition(80, 20);
	go->GetComponentByClass<dae::TextComponent>()->SetText("Programming 4 Assignment", font, SDL_Color{ 255, 255, 255, 255 });
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::FPSComponent>();
	go->SetPosition(0.f, 0.f);
	scene.Add(go);

	auto go2 = std::make_shared<dae::GameObject>();
	go2->AddComponent<dae::TextureComponent>()->SetTexture("pacman.tga");
	go2->SetPosition(320, 240);
	go2->AddComponent<dae::MovementComponent>();
	auto playerlife = go2->AddComponent<dae::PlayerComponent>();
	dae::Singleton<dae::InputManager>::GetInstance().AddControllerCompoundAction(dae::Controller::ButtonInputs::DPadUp,
		dae::Controller::ButtonInputs::DPadDown,
		dae::Controller::ButtonInputs::DPadLeft,
		dae::Controller::ButtonInputs::DPadRight,
		go2.get());
	dae::Singleton<dae::InputManager>::GetInstance().AddControllerActionMapping<dae::Die>(dae::ControllerAction::ActionType::ButtonMap, go2.get(),
		dae::Controller::ButtonInputs::XButton,
		dae::ControllerAction::InputType::ButtonDown);
	dae::Singleton<dae::InputManager>::GetInstance().AddControllerActionMapping<dae::GainPoints>(dae::ControllerAction::ActionType::ButtonMap, go2.get(),
		dae::Controller::ButtonInputs::AButton,
		dae::ControllerAction::InputType::ButtonDown);

	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 13);
	go = std::make_shared<dae::GameObject>();
	auto textComp = go->AddComponent<dae::TextComponent>();
	textComp->SetText("Use WASD to control player one. Use C to take damage and Z to gain points (Keyboard)", font, SDL_Color{ 255, 255, 255, 255 });
	go->SetPosition(0, 60);
	scene.Add(go);
	go = std::make_shared<dae::GameObject>();
	textComp = go->AddComponent<dae::TextComponent>();
	textComp->SetText("Use the Dpad to control player two. Use X Button to take damage and A Button to gain points (XboxController)", font,
		SDL_Color{ 255, 255, 255, 255 });
	go->SetPosition(0, 80);
	scene.Add(go);
	go = std::make_shared<dae::GameObject>();
	auto lifeDisplay = go->AddComponent<dae::LifeDisplayComponent>();
	playerlife->AddObserver(lifeDisplay);
	go->SetPosition(0, 100);
	scene.Add(go);
	go = std::make_shared<dae::GameObject>();
	auto scoreDisplay = go->AddComponent<dae::ScoreDisplayComponent>();
	playerlife->AddObserver(scoreDisplay);
	go->SetPosition(0, 120);
	scene.Add(go);

	scene.Add(go2);

	go2 = std::make_shared<dae::GameObject>();
	go2->AddComponent<dae::TextureComponent>()->SetTexture("pacman.tga");
	go2->SetPosition(200, 200);
	go2->AddComponent<dae::MovementComponent>();
	dae::InputManager::GetInstance().AddCompoundKeyboardAction(SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D, go2.get());
	playerlife = go2->AddComponent<dae::PlayerComponent>();
	dae::Singleton<dae::InputManager>::GetInstance().AddKeyBoardActionMapping<dae::Die>(dae::KeyboardAction::ActionType::ButtonMap,
		dae::KeyboardAction::InputType::OnButtonDown, go2.get(),
		SDL_SCANCODE_C);
	dae::Singleton<dae::InputManager>::GetInstance().AddKeyBoardActionMapping<dae::GainPoints>(
		dae::KeyboardAction::ActionType::ButtonMap, dae::KeyboardAction::InputType::OnButtonDown, go2.get(), SDL_SCANCODE_Z);

	go = std::make_shared<dae::GameObject>();
	lifeDisplay = go->AddComponent<dae::LifeDisplayComponent>();
	playerlife->AddObserver(lifeDisplay);
	go->SetPosition(0, 140);
	scene.Add(go);
	go = std::make_shared<dae::GameObject>();
	scoreDisplay = go->AddComponent<dae::ScoreDisplayComponent>();
	playerlife->AddObserver(scoreDisplay);
	go->SetPosition(0, 160);
	scene.Add(go);
	scene.Add(go2);


}
int main(int, char* [])
{
	dae::Minigin engine{ "../Data/" };
	engine.Run(load);
	return 0;
}