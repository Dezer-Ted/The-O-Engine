#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Minigin.h"

#include <chrono>
#include <thread>

#include "../Input/InputManager.h"
#include "../SceneObjects/Scene.h"
#include "../SceneObjects/SceneManager.h"
#include "../Rendering/Renderer.h"
#include "ResourceManager.h"
#include "Utils/Utils.h"
#include "DeltaTime.h"
#include "Sound/SDLSoundSystem.h"
SDL_Window* g_window{};

void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version);
	printf("We compiled against SDL version %u.%u.%u ...\n",
	       version.major, version.minor, version.patch);

	SDL_GetVersion(&version);
	printf("We are linking against SDL version %u.%u.%u.\n",
	       version.major, version.minor, version.patch);

	SDL_IMAGE_VERSION(&version);
	printf("We compiled against SDL_image version %u.%u.%u ...\n",
	       version.major, version.minor, version.patch);

	version = *IMG_Linked_Version();
	printf("We are linking against SDL_image version %u.%u.%u.\n",
	       version.major, version.minor, version.patch);

	SDL_TTF_VERSION(&version)
	printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
	       version.major, version.minor, version.patch);

	version = *TTF_Linked_Version();
	printf("We are linking against SDL_ttf version %u.%u.%u.\n",
	       version.major, version.minor, version.patch);
}

dae::Minigin::Minigin(const std::string& dataPath)
{
	PrintSDLVersion();

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"Bomberman",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if(g_window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(g_window);

	ResourceManager::GetInstance().Init(dataPath);
}

dae::Minigin::~Minigin()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run(const std::function<void()>& load)
{
	load();

	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();


	bool  doContinue = true;
	auto  last_time{std::chrono::high_resolution_clock::now()};
	float lag{0.f};
	while(doContinue)
	{
		const auto current_time{std::chrono::high_resolution_clock::now()};
		Singleton<DeltaTime>::GetInstance().SetDeltaTime(std::chrono::duration<float>(current_time - last_time).count());
		lag += Singleton<DeltaTime>::GetInstance().GetDeltaTime();
		last_time = current_time;
		doContinue = input.ProcessInput();

		while(lag >= m_Fixed_Time_Step)
		{
			sceneManager.FixedUpdate();
			lag -= m_Fixed_Time_Step;
		}

		sceneManager.Update();
		//SDLSoundSystem::GetInstance().Update();
		sceneManager.LateUpdate();
		renderer.Render();
		sceneManager.CleanUp();
		const auto sleep_time = current_time + Utils::floatToDuration(m_Ms_per_frame) - std::chrono::high_resolution_clock::now();

		std::this_thread::sleep_for(sleep_time);
	}
}
