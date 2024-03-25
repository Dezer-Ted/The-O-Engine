#include "PlayerComponent.h"

dae::PlayerComponent::PlayerComponent(GameObject* pParent) : BaseComponent(pParent)
{
}

void dae::PlayerComponent::AddObserver(Observer* pObserver)
{
	Observable::AddObserver(pObserver);
	NotifyObservers(Utils::GameEvent::PlayerDied, this);
}

void dae::PlayerComponent::AddHP(int amount)
{
	m_CurrentHp += amount;
	NotifyObservers(Utils::GameEvent::PlayerSpawn, this);
}

int dae::PlayerComponent::GetHP() const
{
	return m_CurrentHp;
}

int dae::PlayerComponent::GetScore() const
{
	return m_Score;
}

void dae::PlayerComponent::AddScore(int value)
{
	m_Score += value;
	NotifyObservers(Utils::GameEvent::PlayerGainedPoints, this);
}
