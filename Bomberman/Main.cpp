#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Engine/Minigin.h"
#define WIN32_LEAN_AND_MEAN
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
#include "../Bomberman/Components/PlayerComponent.h"
#include "Components/ColliderComponent.h"
#include "Components/SpriteComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>(&scene);
	auto sprite = go->AddComponent<dae::SpriteComponent>();
	sprite->AddSprite(3, 1, "Character/LeftWalkCycle.png", "WalkLeft");
	sprite->AddSprite(3, 1, "Character/DownWalkCycle.png", "WalkDown");
	sprite->AddSprite(3, 1, "Character/UpWalkCycle.png", "WalkUp");
	sprite->AddSprite(3, 1, "Character/RightWalkCycle.png", "WalkRight");
	sprite->AddSprite(7, 1, "Character/DeathAnimation.png", "DeathAnimation");
	sprite->SwitchToSprite("WalkDown");
	sprite->SetScale(5);
	go->SetPosition(150, 150);
	auto moveComp = go->AddComponent<dae::MovementComponent>();
	dae::Singleton<dae::InputManager>::GetInstance().AddControllerCompoundAction(
		dae::Controller::ButtonInputs::DPadUp,
		dae::Controller::ButtonInputs::DPadDown,
		dae::Controller::ButtonInputs::DPadLeft,
		dae::Controller::ButtonInputs::DPadRight,
		go.get());
	auto playerComp = go->AddComponent<dae::PlayerComponent>();
	moveComp->AddObserver(playerComp);
	auto collider = go->AddComponent<dae::ColliderComponent>();
	collider->AddObserver(playerComp);
	collider->AdjustBoundsToSpriteSize();
	scene.Add(go);
	go = std::make_shared<dae::GameObject>(&scene);
	go->SetPosition(250.f, 250.f);
	go->SetTag("Wall");
	sprite = go->AddComponent<dae::SpriteComponent>();
	sprite->AddSprite(3, 1, "Character/LeftWalkCycle.png", "WalkLeft");
	sprite->SetScale(3.f);
	collider = go->AddComponent<dae::ColliderComponent>();
	collider->AdjustBoundsToSpriteSize();
	scene.Add(go);
}

int main(int, char*[])
{
	dae::Minigin engine{"../Data/"};
	engine.Run(load);
	return 0;
}
