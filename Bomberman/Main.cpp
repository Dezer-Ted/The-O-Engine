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

#include "GridComponent.h"
#include "../Bomberman/Components/PlayerComponent.h"
#include "Commands/DetonateCommand.h"
#include "Commands/MovementCommand.h"
#include "Commands\BombCommand.h"
#include "Components/CameraComponent.h"
#include "Components/ColliderComponent.h"
#include "Components/EncircleComponent.h"
#include "Components/EnemyComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/TextComponent.h"
#include "Components/PowerUpComponent.h"
#include "EnemyStates/HuntingState.h"
#include "EnemyStates/RandomWalkState.h"
#include "EnemyStates/EnemyTransitions/CooldownTransition.h"
#include "EnemyStates/EnemyTransitions/SightedTransition.h"
#include "Engine/DesignPatterns/ServiceLocator.h"
#include "Engine/Sound/DebugSoundSystem.h"
#include "Engine/Sound/SDLSoundSystem.h"
#include "Rendering/Renderer.h"

dae::GameObject* InitPlayer(dae::Scene&         scene, SDL_Rect levelBounds, std::enable_if_t<true, std::shared_ptr<dae::GameObject>>& go,
                            dae::GridComponent* gridComp)
{
	go = std::make_shared<dae::GameObject>(&scene);
	auto powerUpComp = go->AddComponent<dae::PowerUpComponent>();
	auto sprite = go->AddComponent<dae::SpriteComponent>();
	go->SetTag("Player");
	sprite->AddSprite(3, 1, "Character/LeftWalkCycle.png", "WalkLeft");
	sprite->AddSprite(3, 1, "Character/DownWalkCycle.png", "WalkDown");
	sprite->AddSprite(3, 1, "Character/UpWalkCycle.png", "WalkUp");
	sprite->AddSprite(3, 1, "Character/RightWalkCycle.png", "WalkRight");
	sprite->AddSprite(7, 1, "Character/DeathAnimation.png", "DeathAnimation");
	sprite->SwitchToSprite("WalkDown");
	sprite->SetScale(2.5f);
	glm::vec2 startPos = gridComp->GetPositionAtIndex(1, 1);
	go->SetPosition(startPos.x + 5, startPos.y + 5);
	auto moveComp = go->AddComponent<dae::MovementComponent>();
	moveComp->SetSpeed(150.f);
	dae::Singleton<dae::InputManager>::GetInstance().AddControllerCompoundAction<dae::Move>(
		dae::Controller::ButtonInputs::DPadUp,
		dae::Controller::ButtonInputs::DPadDown,
		dae::Controller::ButtonInputs::DPadLeft,
		dae::Controller::ButtonInputs::DPadRight,
		go.get()
	);
	auto playerComp = go->AddComponent<dae::PlayerComponent>();
	playerComp->SetGrid(gridComp);
	dae::Singleton<dae::InputManager>::GetInstance().AddControllerActionMapping<dae::BombCommand>(
		dae::ControllerAction::ActionType::ButtonMap,
		go.get(),
		dae::Controller::ButtonInputs::XButton,
		dae::ControllerAction::InputType::ButtonUp
	);
	dae::Singleton<dae::InputManager>::GetInstance().AddControllerActionMapping<dae::DetonateCommand>(
		dae::ControllerAction::ActionType::ButtonMap,
		go.get(),
		dae::Controller::ButtonInputs::BButton,
		dae::ControllerAction::InputType::ButtonDown
	);
	moveComp->AddObserver(playerComp);
	auto collider = go->AddComponent<dae::ColliderComponent>();
	collider->AddObserver(playerComp);
	collider->AdjustBoundsToSpriteSize();
	collider->AddObserver(moveComp);
	collider->AddObserver(powerUpComp);
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
	spriteComp->AddSprite(4, 1, "Enemies/DeathAnims/BlueDeathAnim.png", "DeathAnim");
	spriteComp->AddSprite(4, 1, "Enemies/Oneal/Walk.png", "Walk");
	spriteComp->SetScale(2.5f);
	auto collider{go->AddComponent<dae::ColliderComponent>()};
	collider->AdjustBoundsToSpriteSize();
	auto moveComp{go->AddComponent<dae::MovementComponent>()};
	collider->AddObserver(moveComp);
	auto enemyComp{go->AddComponent<dae::EnemyComponent>()};
	spriteComp->AddObserver(enemyComp);
	collider->AddObserver(enemyComp);
	auto walkState{std::make_unique<dae::RandomWalkState>(go.get())};
	collider->AddObserver(walkState.get());
	auto startState = enemyComp->AddState(std::move(walkState));

	auto huntState{std::make_unique<dae::HuntingState>(player, gridComp, go.get())};
	auto pHuntState = enemyComp->AddState(std::move(huntState));
	auto sightedTransition{std::make_unique<dae::SightedTransition>(startState, pHuntState, player, go.get(), gridComp, false)};
	enemyComp->AddTransition(std::move(sightedTransition));
	auto cooldownTransition{std::make_unique<dae::CooldownTransition>(pHuntState, startState, 2.f)};
	enemyComp->AddTransition(std::move(cooldownTransition));
	sightedTransition = std::make_unique<dae::SightedTransition>(pHuntState, pHuntState, player, go.get(), gridComp, false);
	enemyComp->AddTransition(std::move(sightedTransition));
	enemyComp->SetState(startState);
	scene.Add(go);


	dae::Renderer::GetInstance().SetBackgroundColor(SDL_Color{57, 132, 0, 1});
}

int main(int, char*[])
{
	dae::Minigin engine{"../Data/"};
	engine.Run(load);
	return 0;
}
