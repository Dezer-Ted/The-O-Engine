#if _DEBUG
#if __has_include(<vld.h>)
#endif
#endif
#include "Engine/Minigin.h"
#define WIN32_LEAN_AND_MEAN
#include <memory>
#include <memory>
#include <Windows.h>
#include <Engine/ResourceManager.h>
#include <Input/InputManager.h>
#include <Components/MiscFunctionComponent.h>
#include <Components/TrashTheCacheComponent.h>
#include "Components/EnemyComponent.h"
#include "Components/TextComponent.h"
#include "Engine/DesignPatterns/ServiceLocator.h"
#include "Engine/Sound/DebugSoundSystem.h"
#include "Engine/Sound/SDLSoundSystem.h"
#include "Rendering/Renderer.h"
#include "SceneUtils/LevelLoader.h"
#include "SceneUtils/MenuLoader.h"

void load()
{
	#ifdef NDEBUG
	dae::ServiceLocator::RegisterSoundSystem(std::make_unique<dae::SDLSoundSystem>());
	#else
	dae::ServiceLocator::RegisterSoundSystem(std::make_unique<dae::DebugSoundSystem>(std::make_unique<dae::SDLSoundSystem>()));
	#endif

	//dae::LevelLoader::LoadLevel("LevelData/Level0.json");
	//dae::MenuLoader::LoadStartScreen();
	dae::MenuLoader::LoadEndScreen();

}

int main(int, char*[])
{
	srand(static_cast<unsigned int>(time(NULL)));
	dae::Minigin engine{"../Data/"};
	engine.Run(load);
	return 0;
}
