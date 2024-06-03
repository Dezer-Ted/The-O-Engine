#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Engine/Minigin.h"
#define WIN32_LEAN_AND_MEAN
#include <memory>
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

#include "GridComponent.h"
#include "../Bomberman/Components/PlayerComponent.h"
#include "Commands/MovementCommand.h"
#include "Commands\BombCommand.h"
#include "Components/CameraComponent.h"
#include "Components/ColliderComponent.h"
#include "Components/EncircleComponent.h"
#include "Components/OnealComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/TextComponent.h"
#include "Engine/DesignPatterns/ServiceLocator.h"
#include "Engine/Sound/DebugSoundSystem.h"
#include "Engine/Sound/SDLSoundSystem.h"
#include "Rendering/Renderer.h"

dae::GameObject* InitPlayer(dae::Scene&         scene, SDL_Rect levelBounds, std::enable_if_t<true, std::shared_ptr<dae::GameObject>>& go,
                            dae::GridComponent* gridComp)
{
	go = std::make_shared<dae::GameObject>(&scene);
	auto sprite = go->AddComponent<dae::SpriteComponent>();
	sprite->AddSprite(3, 1, "Character/LeftWalkCycle.png", "WalkLeft");
	sprite->AddSprite(3, 1, "Character/DownWalkCycle.png", "WalkDown");
	sprite->AddSprite(3, 1, "Character/UpWalkCycle.png", "WalkUp");
	sprite->AddSprite(3, 1, "Character/RightWalkCycle.png", "WalkRight");
	sprite->AddSprite(7, 1, "Character/DeathAnimation.png", "DeathAnimation");
	sprite->SwitchToSprite("WalkDown");
	sprite->SetScale(2.5f);
	glm::vec2 startPos = gridComp->GetPositionAtIndex(1, 1);
	go->SetPosition(startPos.x, startPos.y);
	auto moveComp = go->AddComponent<dae::MovementComponent>();
	moveComp->SetSpeed(150.f);
	dae::Singleton<dae::InputManager>::GetInstance().AddControllerCompoundAction<dae::Move>(
		dae::Controller::ButtonInputs::DPadUp,
		dae::Controller::ButtonInputs::DPadDown,
		dae::Controller::ButtonInputs::DPadLeft,
		dae::Controller::ButtonInputs::DPadRight,
		go.get());
	auto playerComp = go->AddComponent<dae::PlayerComponent>();
	playerComp->SetGrid(gridComp);
	dae::Singleton<dae::InputManager>::GetInstance().AddControllerActionMapping<dae::BombCommand>(
		dae::ControllerAction::ActionType::ButtonMap, go.get(), dae::Controller::ButtonInputs::XButton, dae::ControllerAction::InputType::ButtonUp);
	moveComp->AddObserver(playerComp);
	auto collider = go->AddComponent<dae::ColliderComponent>();
	collider->AddObserver(playerComp);
	collider->AdjustBoundsToSpriteSize();
	collider->AddObserver(moveComp);
	auto cam = go->AddComponent<dae::CameraComponent>();
	cam->SetBounds(levelBounds);
	scene.Add(go);
	return go.get();
}

void InitGrid(dae::Scene& scene, SDL_Rect levelBounds, std::enable_if_t<true, std::shared_ptr<dae::GameObject>> go, dae::GridComponent*& gridComp)
{
	gridComp = go->AddComponent<dae::GridComponent>();
	gridComp->InitGrid(levelBounds.w, levelBounds.h, 31, 13);
	gridComp->CreateWallObjects(scene);
	scene.Add(go);
}

void load()
{
	#ifdef NDEBUG
	dae::ServiceLocator::RegisterSoundSystem(std::make_unique<dae::SDLSoundSystem>());
	#else
	dae::ServiceLocator::RegisterSoundSystem(std::make_unique<dae::DebugSoundSystem>(std::make_unique<dae::SDLSoundSystem>()));
	#endif
	auto&               scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	SDL_Rect            levelBounds{0, 0, 1395, 624};
	auto                go = std::make_shared<dae::GameObject>(&scene);
	dae::GridComponent* gridComp;
	InitGrid(scene, levelBounds, go, gridComp);

	auto player = InitPlayer(scene, levelBounds, go, gridComp);

	go = std::make_shared<dae::GameObject>(&scene);
	go->SetTag("Enemy");
	auto pos{gridComp->GetPositionAtIndex(3, 3)};
	go->SetPosition(pos.x + 3, pos.y + 3);
	auto spriteComp{go->AddComponent<dae::SpriteComponent>()};
	spriteComp->AddSprite(4, 1, "Enemies/Oneal/Walk.png", "Walk");
	spriteComp->SetScale(2.5f);
	auto collider{go->AddComponent<dae::ColliderComponent>()};
	collider->AdjustBoundsToSpriteSize();
	go->AddComponent<dae::MovementComponent>();
	auto enemy{go->AddComponent<dae::OnealComponent>()};
	collider->AddObserver(enemy);
	enemy->Initialize(gridComp, player);
	//scene.Add(go);


	dae::Renderer::GetInstance().SetBackgroundColor(SDL_Color{57, 132, 0, 1});
}

int main(int, char*[])
{
	dae::Minigin engine{"../Data/"};
	engine.Run(load);
	return 0;
}
