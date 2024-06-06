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
#include "SceneUtils/EnemyLoader.h"
#include "SceneUtils/LevelLoader.h"
#include "SceneUtils/PlayerLoader.h"


/*void InitGrid(dae::Scene& scene, SDL_Rect levelBounds, std::enable_if_t<true, std::shared_ptr<dae::GameObject>> go, dae::GridComponent*& gridComp)
{
	gridComp = go->AddComponent<dae::GridComponent>();
	gridComp->InitGrid(levelBounds.w, levelBounds.h, 31, 13);
	gridComp->CreateWallObjects(scene);
	scene.Add(go);
}*/

void load()
{
	#ifdef NDEBUG
	dae::ServiceLocator::RegisterSoundSystem(std::make_unique<dae::SDLSoundSystem>());
	#else
	dae::ServiceLocator::RegisterSoundSystem(std::make_unique<dae::DebugSoundSystem>(std::make_unique<dae::SDLSoundSystem>()));
	#endif

	dae::LevelLoader::LoadLevel("LevelData/Level1.json");

	dae::Renderer::GetInstance().SetBackgroundColor(SDL_Color{57, 132, 0, 1});
}

int main(int, char*[])
{
	srand(static_cast<unsigned int>(time(NULL)));
	dae::Minigin engine{"../Data/"};
	engine.Run(load);
	return 0;
}
