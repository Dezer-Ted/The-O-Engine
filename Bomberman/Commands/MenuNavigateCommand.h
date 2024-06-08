#pragma once
#include "Engine/DesignPatterns/Command.h"


namespace dae
{
	class MenuNavigatorComponent;

	class MenuNavigateCommand final : public dae::GameObjectCommand {
	public:
		MenuNavigateCommand(GameObject* pParent);
		MenuNavigateCommand(const MenuNavigateCommand& other) = delete;
		MenuNavigateCommand(MenuNavigateCommand&& other) noexcept = delete;
		MenuNavigateCommand& operator=(const MenuNavigateCommand& other) = delete;
		MenuNavigateCommand& operator=(MenuNavigateCommand&& other) noexcept = delete;
		~MenuNavigateCommand() override = default;

		void Execute2DAxis(const glm::vec2& input) override;

	private:
		MenuNavigatorComponent* m_MenuComp{nullptr};
	};
}
