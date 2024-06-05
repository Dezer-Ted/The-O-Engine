#include "WallComponent.h"

#include <ranges>

#include "PowerUpPickUpComponent.h"
#include "Components/ColliderComponent.h"
#include "SceneObjects/GameObject.h"
#include "Components/SpriteComponent.h"
#include "SceneObjects/Scene.h"

dae::WallComponent::WallComponent(GameObject* pOwner) : BaseComponent(pOwner)
{
	m_pSpriteComponent = pOwner->GetComponentByClass<SpriteComponent>();
}

void dae::WallComponent::StartDestruction()
{
	m_pSpriteComponent->SwitchToSprite("DestructionAnimation");
	m_pSpriteComponent->ShouldUpdate(true);
	m_IsDestroyed = true;
}

void dae::WallComponent::Notify(Utils::GameEvent event, ObserverEventData* eventData)
{
	switch(event)
	{
	case Utils::GameEvent::AnimationEnded:
		if(!m_IsDestroyed)
			return;
		if(m_HoldsItem)
			DropItem();
		GetParent()->DestroyObject();
		break;
	}
}

void dae::WallComponent::SetPowerUp(PowerUps powerUp)
{
	m_PowerUp = powerUp;
	m_HoldsItem = true;
}

void dae::WallComponent::DropItem() const
{
	auto go = std::make_shared<GameObject>(GetParent()->GetParentScene());
	go->SetTag("PowerUp");
	auto spriteComp = go->AddComponent<SpriteComponent>();
	switch(m_PowerUp)
	{
	case PowerUps::BombUp:
		spriteComp->AddSprite(1, 1, "PowerUps/BombUp.png", "Base");
		break;
	case PowerUps::FireUp:
		spriteComp->AddSprite(1, 1, "PowerUps/FireUp.png", "Base");
		break;
	case PowerUps::Detonator:
		spriteComp->AddSprite(1, 1, "PowerUps/Detonate.png", "Base");
		break;
	}
	auto pos = GetParent()->GetTransform().GetWorldPosition();
	go->SetPosition(pos.x, pos.y);
	spriteComp->ShouldUpdate(false);
	spriteComp->SetScale(2.5f);
	auto pickUpComp = go->AddComponent<PowerUpPickUpComponent>();
	pickUpComp->SetPowerUp(m_PowerUp);
	auto collComp = go->AddComponent<ColliderComponent>();
	collComp->AdjustBoundsToSpriteSize();
	collComp->AddObserver(pickUpComp);
	GetParent()->GetParentScene()->Add(go);
}
