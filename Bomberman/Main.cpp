#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Engine/Minigin.h"
#define WIN32_LEAN_AND_MEAN
#include <memory>
#include <Windows.h>
#include <SceneObjects/GameObject.h>
#include "Engine/DesignPatterns/Observable.h"
#include <SceneObjects/SceneManager.h>
#include <Engine/ResourceManager.h>
#include <SceneObjects/Scene.h>
#include <Input/InputManager.h>
#include <Components/MiscFunctionComponent.h>
#include <Components/TrashTheCacheComponent.h>
#include "Components/MovementComponent.h"
#include <Engine/DesignPatterns/Command.h>

#include "Grid.h"
#include "../Bomberman/Components/PlayerComponent.h"
#include "Components/CameraComponent.h"
#include "Components/ColliderComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/TextComponent.h"
#include "Engine/DesignPatterns/ServiceLocator.h"
#include "Engine/Sound/DebugSoundSystem.h"
#include "Engine/Sound/SDLSoundSystem.h"
#include "Rendering/Renderer.h"

void load()
{
	#ifdef NDEBUG
	dae::ServiceLocator::RegisterSoundSystem(std::make_unique<dae::SDLSoundSystem>());
	#else
	dae::ServiceLocator::RegisterSoundSystem(std::make_unique<dae::DebugSoundSystem>(std::make_unique<dae::SDLSoundSystem>()));
	#endif
	auto&     scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	SDL_Rect  levelBounds{0, 0, 1395, 624};
	dae::Grid grid(levelBounds.w, levelBounds.h, 31, 13);
	grid.InitWalls(scene);
	auto go = std::make_shared<dae::GameObject>(&scene);
	auto sprite = go->AddComponent<dae::SpriteComponent>();
	sprite->AddSprite(3, 1, "Character/LeftWalkCycle.png", "WalkLeft");
	sprite->AddSprite(3, 1, "Character/DownWalkCycle.png", "WalkDown");
	sprite->AddSprite(3, 1, "Character/UpWalkCycle.png", "WalkUp");
	sprite->AddSprite(3, 1, "Character/RightWalkCycle.png", "WalkRight");
	sprite->AddSprite(7, 1, "Character/DeathAnimation.png", "DeathAnimation");
	sprite->SwitchToSprite("WalkDown");
	sprite->SetScale(2.5f);
	glm::vec2 startPos = grid.GetStartPosition();
	go->SetPosition(startPos.x, startPos.y);
	auto moveComp = go->AddComponent<dae::MovementComponent>();
	moveComp->SetSpeed(150.f);
	dae::Singleton<dae::InputManager>::GetInstance().AddControllerCompoundAction(
		dae::Controller::ButtonInputs::DPadUp,
		dae::Controller::ButtonInputs::DPadDown,
		dae::Controller::ButtonInputs::DPadLeft,
		dae::Controller::ButtonInputs::DPadRight,
		go.get());
	dae::Singleton<dae::InputManager>::GetInstance().AddControllerActionMapping<dae::PlaySound>(
		dae::ControllerAction::ActionType::ButtonMap, go.get(), dae::Controller::ButtonInputs::XButton, dae::ControllerAction::InputType::ButtonUp);
	auto playerComp = go->AddComponent<dae::PlayerComponent>();
	moveComp->AddObserver(playerComp);
	auto collider = go->AddComponent<dae::ColliderComponent>();
	collider->AddObserver(playerComp);
	collider->AdjustBoundsToSpriteSize();
	auto cam = go->AddComponent<dae::CameraComponent>();
	cam->SetBounds(levelBounds);
	scene.Add(go);
	go = std::make_shared<dae::GameObject>(&scene);
	auto textComp = go->AddComponent<dae::TextComponent>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 26);
	textComp->SetText("Press X to Play explosion Sound", font, SDL_Color{255, 0, 0, 255});
	scene.Add(go);
	dae::Renderer::GetInstance().SetBackgroundColor(SDL_Color{57, 132, 0});
}

int main(int, char*[])
{
	dae::Minigin engine{"../Data/"};
	engine.Run(load);
	return 0;
}
