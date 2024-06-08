#pragma once
#include "Engine/DesignPatterns/Command.h"


namespace dae
{
	class MenuNavigatorComponent;

	class MenuSelectCommand final : public dae::GameObjectCommand {
	public:
		MenuSelectCommand(dae::GameObject* pParent);
		MenuSelectCommand(const MenuSelectCommand& other) = delete;
		MenuSelectCommand(MenuSelectCommand&& other) noexcept = delete;
		MenuSelectCommand& operator=(const MenuSelectCommand& other) = delete;
		MenuSelectCommand& operator=(MenuSelectCommand&& other) noexcept = delete;
		~MenuSelectCommand() override = default;
		void Execute() override;

	private:
		MenuNavigatorComponent* m_pNavComp{nullptr};
	};
}
