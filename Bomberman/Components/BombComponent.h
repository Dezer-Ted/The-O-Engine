#pragma once
#include "Components/BaseComponent.h"

class BombComponent final : public dae::BaseComponent {
public:
	BombComponent(dae::GameObject* pOwner);
	BombComponent(const BombComponent& other) = delete;
	BombComponent(BombComponent&& other) noexcept = delete;
	BombComponent& operator=(const BombComponent& other) = delete;
	BombComponent& operator=(BombComponent&& other) noexcept = delete;
	~BombComponent() override = default;
private:
	
};
