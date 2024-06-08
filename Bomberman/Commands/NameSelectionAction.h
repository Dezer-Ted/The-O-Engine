#pragma once
#include "Engine/DesignPatterns/Command.h"



namespace dae
{
	
	class NameSelectionComponent;
	class NameSelectionAction final : public dae::GameObjectCommand {
	public:
		NameSelectionAction(GameObject* pParent);
		NameSelectionAction(const NameSelectionAction& other) = delete;
		NameSelectionAction(NameSelectionAction&& other) noexcept = delete;
		NameSelectionAction& operator=(const NameSelectionAction& other) = delete;
		NameSelectionAction& operator=(NameSelectionAction&& other) noexcept = delete;
		~NameSelectionAction() override = default;
		void Execute2DAxis(const glm::vec2& input) override;

	private:
		NameSelectionComponent* m_pNameSelectionComp{nullptr};
    };

}
