#include "PlayerLoader.h"

#include "Components/SpriteComponent.h"
#include "../Components/PowerUpComponent.h"
#include "../Components/MovementComponent.h"
#include "Input/InputManager.h"
#include "../Commands/MovementCommand.h"
#include "../Commands/BombCommand.h"
#include "../Components/PlayerComponent.h"
#include "../Commands/DetonateCommand.h"
#include "Components/ColliderComponent.h"
#include "Components/CameraComponent.h"


dae::GameObject* dae::PlayerLoader::LoadPlayer(Scene* pScene, const SDL_Rect& levelBounds, GridComponent* pGrid)
{
	auto go = std::make_shared<dae::GameObject>(pScene);
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
	glm::vec2 startPos = pGrid->GetPositionAtIndex(1, 1);
	go->SetPosition(startPos.x + 5, startPos.y + 5);

	auto collider = go->AddComponent<dae::ColliderComponent>();
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
	playerComp->SetGrid(pGrid);
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
	collider->AddObserver(playerComp);
	collider->AdjustBoundsToSpriteSize();
	collider->AddObserver(moveComp);
	collider->AddObserver(powerUpComp);
	auto cam = go->AddComponent<dae::CameraComponent>();
	cam->SetBounds(levelBounds);
	pScene->Add(go);
	return go.get();
}
