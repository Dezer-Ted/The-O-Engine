#pragma once
#include "Engine/DesignPatterns/Command.h"

namespace dae
{
	class PlayerComponent;

	class BombCommand final : public dae::GameObjectCommand {
	public:
		BombCommand(dae::GameObject* pOwner);
		BombCommand(const BombCommand& other) = delete;
		BombCommand(BombCommand&& other) noexcept = delete;
		BombCommand& operator=(const BombCommand& other) = delete;
		BombCommand& operator=(BombCommand&& other) noexcept = delete;

		void Execute() override;
		~BombCommand() override= default;

	private:
		dae::PlayerComponent* m_pPlayerComp;
	};
}
