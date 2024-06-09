#pragma once
#include "Engine/DesignPatterns/Command.h"

class MuteCommand final : public dae::GameObjectCommand {
public:
	MuteCommand(dae::GameObject* pParent);
	MuteCommand(const MuteCommand& other) = delete;
	MuteCommand(MuteCommand&& other) noexcept = delete;
	MuteCommand& operator=(const MuteCommand& other) = delete;
	MuteCommand& operator=(MuteCommand&& other) noexcept = delete;
	~MuteCommand() override = default;
	void Execute() override;
};
