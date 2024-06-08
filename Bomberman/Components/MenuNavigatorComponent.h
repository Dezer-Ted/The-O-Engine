#pragma once
#include <vector>

#include "Components/BaseComponent.h"

namespace dae
{
	class MenuNavigatorComponent final : public dae::BaseComponent {
	public:
		MenuNavigatorComponent(dae::GameObject* pParent);
		MenuNavigatorComponent(const MenuNavigatorComponent& other) = delete;
		MenuNavigatorComponent(MenuNavigatorComponent&& other) noexcept = delete;
		MenuNavigatorComponent& operator=(const MenuNavigatorComponent& other) = delete;
		MenuNavigatorComponent& operator=(MenuNavigatorComponent&& other) noexcept = delete;
		~MenuNavigatorComponent() override = default;
		void MoveUp();
		void MoveDown();
		void ExecuteCurrentlySelected() const;
		void RegisterMenuItem(GameObject* pMenuItem);
		void Update() override;
	private:
		void                     UpdateIndicatorPosition() const;
		std::vector<GameObject*> m_MenuObjects;
		int                      m_CurrentlySelectedItem{0};
		const float              m_SwitchCooldown{0.2f};
		float                    m_CurrentCooldown{0.f};
		bool                     m_IsOnCooldown{false};
	};
}
