#pragma once
#include "Engine/DesignPatterns/Command.h"

namespace dae
{
	class DetonateCommand final : public dae::GameObjectCommand {
	public:
		DetonateCommand(GameObject* pOwner);
		DetonateCommand(const DetonateCommand& other) = delete;
		DetonateCommand(DetonateCommand&& other) noexcept = delete;
		DetonateCommand& operator=(const DetonateCommand& other) = delete;
		DetonateCommand& operator=(DetonateCommand&& other) noexcept = delete;
		~DetonateCommand() override = default;
		void Execute() override;

	private:
		PlayerComponent* m_pPlayerComponent;
	};
}
