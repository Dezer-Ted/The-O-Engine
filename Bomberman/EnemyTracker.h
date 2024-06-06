#pragma once
#include "Engine/DesignPatterns/Observer.h"
#include "Engine/DesignPatterns/Singleton.h"

class EnemyTracker final : public dae::Singleton<EnemyTracker>, public dae::Observer {
public:
	EnemyTracker(const EnemyTracker& other) = delete;
	EnemyTracker(EnemyTracker&& other) noexcept = delete;
	EnemyTracker& operator=(const EnemyTracker& other) = delete;
	EnemyTracker& operator=(EnemyTracker&& other) noexcept = delete;

	void Notify(Utils::GameEvent event, dae::ObserverEventData* eventData) override;

private:
	friend class Singleton<EnemyTracker>;
	EnemyTracker() = default;
};
