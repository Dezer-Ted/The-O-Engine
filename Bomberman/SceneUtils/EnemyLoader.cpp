#include "EnemyLoader.h"

#include "../EnemyTracker.h"
#include "Components/SpriteComponent.h"
#include "Components/ColliderComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/EnemyComponent.h"
#include "../EnemyStates/HuntingState.h"
#include "../EnemyStates/RandomWalkState.h"
#include "../EnemyStates/EnemyTransitions/CooldownTransition.h"
#include "../EnemyStates/EnemyTransitions/SightedTransition.h"


dae::GameObject* dae::EnemyLoader::LoadOneal(Scene* pScene, const std::vector<GameObject*>& players, GridComponent* pGrid, const glm::vec2& position)
{
	auto go = std::make_shared<dae::GameObject>(pScene);
	go->SetTag("Enemy");
	go->SetPosition(position.x, position.y);
	auto spriteComp{go->AddComponent<dae::SpriteComponent>()};
	spriteComp->AddSprite(4, 1, "Enemies/DeathAnims/BlueDeathAnim.png", "DeathAnim");
	spriteComp->AddSprite(4, 1, "Enemies/Oneal/Walk.png", "Walk");
	spriteComp->SetScale(2.5f);
	auto collider{go->AddComponent<dae::ColliderComponent>()};
	collider->AdjustBoundsToSpriteSize();
	auto moveComp{go->AddComponent<dae::MovementComponent>()};
	collider->AddObserver(moveComp);
	auto enemyComp{go->AddComponent<dae::EnemyComponent>()};
	enemyComp->SetEnemyType(EnemyType::Oneal);
	spriteComp->AddObserver(enemyComp);
	collider->AddObserver(enemyComp);
	auto walkState{std::make_unique<dae::RandomWalkState>(go.get())};
	collider->AddObserver(walkState.get());
	auto startState = enemyComp->AddState(std::move(walkState));

	auto huntState{std::make_unique<dae::HuntingState>(pGrid, go.get())};
	auto pHuntState = enemyComp->AddState(std::move(huntState));
	auto sightedTransition{std::make_unique<dae::SightedTransition>(startState, pHuntState, players, go.get(), pGrid, false)};
	sightedTransition->AddObserver(dynamic_cast<HuntingState*>(pHuntState));
	enemyComp->AddTransition(std::move(sightedTransition));
	auto cooldownTransition{std::make_unique<dae::CooldownTransition>(pHuntState, startState, 2.f)};
	enemyComp->AddTransition(std::move(cooldownTransition));
	sightedTransition = std::make_unique<dae::SightedTransition>(pHuntState, pHuntState, players, go.get(), pGrid, false);
	enemyComp->AddTransition(std::move(sightedTransition));
	enemyComp->SetState(startState);
	enemyComp->AddObserver(&EnemyTracker::GetInstance());
	pScene->Add(go);
	return go.get();
}

dae::GameObject* dae::EnemyLoader::LoadBalloom(Scene* pScene, const glm::vec2& position)
{
	auto go = std::make_shared<dae::GameObject>(pScene);
	go->SetTag("Enemy");
	go->SetPosition(position.x, position.y);
	auto spriteComp{go->AddComponent<dae::SpriteComponent>()};
	spriteComp->AddSprite(4, 1, "Enemies/DeathAnims/OrangeDeathAnim.png", "DeathAnim");
	spriteComp->AddSprite(4, 1, "Enemies/Balloom/Walk.png", "Walk");
	spriteComp->SetScale(2.5f);
	auto collider{go->AddComponent<dae::ColliderComponent>()};
	collider->AdjustBoundsToSpriteSize();
	auto moveComp{go->AddComponent<dae::MovementComponent>()};
	moveComp->SetSpeed(50.f);
	collider->AddObserver(moveComp);
	auto enemyComp{go->AddComponent<dae::EnemyComponent>()};
	enemyComp->SetEnemyType(EnemyType::Balloom);
	spriteComp->AddObserver(enemyComp);
	collider->AddObserver(enemyComp);
	auto walkState{std::make_unique<dae::RandomWalkState>(go.get())};
	collider->AddObserver(walkState.get());
	auto startState = enemyComp->AddState(std::move(walkState));
	enemyComp->SetState(startState);
	enemyComp->AddObserver(&EnemyTracker::GetInstance());
	pScene->Add(go);
	return go.get();
}

dae::GameObject* dae::EnemyLoader::LoadDoll(Scene* pScene, const glm::vec2& position)
{
	auto go = std::make_shared<dae::GameObject>(pScene);
	go->SetTag("Enemy");
	go->SetPosition(position.x, position.y);
	auto spriteComp{go->AddComponent<dae::SpriteComponent>()};
	spriteComp->AddSprite(4, 1, "Enemies/DeathAnims/PurpleDeathAnim.png", "DeathAnim");
	spriteComp->AddSprite(4, 1, "Enemies/Doll/Walk.png", "Walk");
	spriteComp->SetScale(2.5f);
	auto collider{go->AddComponent<dae::ColliderComponent>()};
	collider->AdjustBoundsToSpriteSize();
	auto moveComp{go->AddComponent<dae::MovementComponent>()};
	collider->AddObserver(moveComp);
	auto enemyComp{go->AddComponent<dae::EnemyComponent>()};
	enemyComp->SetEnemyType(EnemyType::Doll);
	spriteComp->AddObserver(enemyComp);
	collider->AddObserver(enemyComp);
	auto walkState{std::make_unique<dae::RandomWalkState>(go.get())};
	collider->AddObserver(walkState.get());
	auto startState = enemyComp->AddState(std::move(walkState));
	enemyComp->SetState(startState);
	enemyComp->AddObserver(&EnemyTracker::GetInstance());
	pScene->Add(go);
	return go.get();
}

dae::GameObject* dae::EnemyLoader::LoadMinvo(Scene* pScene, const std::vector<GameObject*>& players, GridComponent* pGrid, const glm::vec2& position)
{
	auto go = std::make_shared<dae::GameObject>(pScene);
	go->SetTag("Enemy");
	go->SetPosition(position.x, position.y);
	auto spriteComp{go->AddComponent<dae::SpriteComponent>()};
	spriteComp->AddSprite(4, 1, "Enemies/DeathAnims/OrangeDeathAnim.png", "DeathAnim");
	spriteComp->AddSprite(4, 1, "Enemies/Minvo/Walk.png", "Walk");
	spriteComp->SetScale(2.5f);
	auto collider{go->AddComponent<dae::ColliderComponent>()};
	collider->AdjustBoundsToSpriteSize();
	auto moveComp{go->AddComponent<dae::MovementComponent>()};
	moveComp->SetSpeed(125.f);
	collider->AddObserver(moveComp);
	auto enemyComp{go->AddComponent<dae::EnemyComponent>()};
	enemyComp->SetEnemyType(EnemyType::Minvo);
	spriteComp->AddObserver(enemyComp);
	collider->AddObserver(enemyComp);
	auto walkState{std::make_unique<dae::RandomWalkState>(go.get())};
	collider->AddObserver(walkState.get());
	auto startState = enemyComp->AddState(std::move(walkState));

	auto huntState{std::make_unique<dae::HuntingState>(pGrid, go.get())};
	auto pHuntState = enemyComp->AddState(std::move(huntState));
	auto sightedTransition{std::make_unique<dae::SightedTransition>(startState, pHuntState, players, go.get(), pGrid, false)};
	sightedTransition->AddObserver(dynamic_cast<HuntingState*>(pHuntState));
	enemyComp->AddTransition(std::move(sightedTransition));
	auto cooldownTransition{std::make_unique<dae::CooldownTransition>(pHuntState, startState, 2.f)};
	enemyComp->AddTransition(std::move(cooldownTransition));
	sightedTransition = std::make_unique<dae::SightedTransition>(pHuntState, pHuntState, players, go.get(), pGrid, false);
	enemyComp->AddTransition(std::move(sightedTransition));
	enemyComp->SetState(startState);
	enemyComp->AddObserver(&EnemyTracker::GetInstance());
	pScene->Add(go);
	return go.get();
}
