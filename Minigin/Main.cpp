#pragma once
#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif
#include "GameObject.h"
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "Utils.h"
#include "Components/EncircleComponent.h"
#include "Components/FPSComponent.h"
#include "Components/MiscFunctionComponent.h"
#include "Components/TextComponent.h"
#include "Components/TextureComponent.h"
#include "Components/TrashTheCacheComponent.h"

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
	go->GetComponentByClass<dae::TextComponent>()->SetText("Programming 4 Assignment", font, SDL_Color{255, 255, 255, 255});
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::FPSComponent>();
	go->SetPosition(0.f, 0.f);
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->AddComponent<dae::TextureComponent>()->SetTexture("pacman.tga");
	go->SetPosition(320, 240);
	auto encirleComp = go->AddComponent<dae::EncircleComponent>();
	encirleComp->SetRadius(100.f);

	auto go2 = std::make_shared<dae::GameObject>();
	go2->AddComponent<dae::TextureComponent>()->SetTexture("pacman.tga");
	go2->SetPosition(50, 50);
	encirleComp = go2->AddComponent<dae::EncircleComponent>();
	encirleComp->SetRadius(100.f);
	go2->SetParent(go.get());
	scene.Add(go);
	scene.Add(go2);
	go = std::make_shared<dae::GameObject>();
	auto comp = go->AddComponent<TrashTheCacheComponent>();
	static_cast<void*>(comp);
	scene.Add(go);
}

int main(int, char*[])
{
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}
