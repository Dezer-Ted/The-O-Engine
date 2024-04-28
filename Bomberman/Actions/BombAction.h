#pragma once
#include "Engine/DesignPatterns/Command.h"

namespace dae
{
	class PlayerComponent;

	class BombAction final : dae::GameObjectCommand {
	public:
		BombAction(dae::GameObject* pOwner);
		BombAction(const BombAction& other) = delete;
		BombAction(BombAction&& other) noexcept = delete;
		BombAction& operator=(const BombAction& other) = delete;
		BombAction& operator=(BombAction&& other) noexcept = delete;

		void Execute() override;
		~BombAction() override = default;
	private:
		dae::PlayerComponent* m_pPlayerComp;
	};
}
