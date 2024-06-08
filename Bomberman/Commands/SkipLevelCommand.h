#pragma once
#include "Engine/DesignPatterns/Command.h"

namespace dae
{
	class SkipLevelCommand final : public dae::GameObjectCommand {
	public:
		SkipLevelCommand(GameObject* pParent);
		SkipLevelCommand(const SkipLevelCommand& other) = delete;
		SkipLevelCommand(SkipLevelCommand&& other) noexcept = delete;
		SkipLevelCommand& operator=(const SkipLevelCommand& other) = delete;
		SkipLevelCommand& operator=(SkipLevelCommand&& other) noexcept = delete;
		~SkipLevelCommand() override = default;
		void Execute() override;
	};
}
