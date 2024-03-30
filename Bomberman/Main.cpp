#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <GameObject.h>
#include "Observable.h"
#include <Minigin.h>
#include <SceneManager.h>
#include <ResourceManager.h>
#include <Scene.h>
#include <InputManager.h>
#include <Utils.h>
#include <Components/MiscFunctionComponent.h>
#include <Components/TrashTheCacheComponent.h>
#include "Components/MovementComponent.h"
#include <Command.h>
#include "../Bomberman/Components/PlayerComponent.h"
#include "Components/SpriteComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>();
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
	scene.Add(go);
}

int main(int, char*[])
{
	dae::Minigin engine{"../Data/"};
	engine.Run(load);
	return 0;
}
