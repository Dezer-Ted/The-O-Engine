#pragma once
#include "Engine/DesignPatterns/Command.h"



namespace dae
{
	
	class NameSelectionComponent;
	class SaveScoreCommand final : public dae::GameObjectCommand {
	public:
		SaveScoreCommand(dae::GameObject* pParent);
		SaveScoreCommand(const SaveScoreCommand& other) = delete;
		SaveScoreCommand(SaveScoreCommand&& other) noexcept = delete;
		SaveScoreCommand& operator=(const SaveScoreCommand& other) = delete;
		SaveScoreCommand& operator=(SaveScoreCommand&& other) noexcept = delete;
		~SaveScoreCommand() override = default;
		void Execute() override;

	private:
		NameSelectionComponent* m_pNameSelecComp{nullptr};
		
	};
}
