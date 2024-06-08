#pragma once
#include <vector>

#include "Components/BaseComponent.h"


namespace dae
{
	class HighScoreListComponent;
}

namespace dae
{
	class GameObject;
	class CharacterScrollComponent;

	class NameSelectionComponent final : public dae::BaseComponent {
	public:
		NameSelectionComponent(dae::GameObject* pParent);
		NameSelectionComponent(const NameSelectionComponent& other) = delete;
		NameSelectionComponent(NameSelectionComponent&& other) noexcept = delete;
		NameSelectionComponent& operator=(const NameSelectionComponent& other) = delete;
		NameSelectionComponent& operator=(NameSelectionComponent&& other) noexcept = delete;
		~NameSelectionComponent() override = default;
		void RegisterCharacter(CharacterScrollComponent* pCharacter);
		void RegisterIndicators(GameObject* pIndicatorUp, GameObject* pIndicatorDown);
		void MoveIndicatorLeft();
		void MoveIndicatorRight();
		void ScrollCurrentCharacterUp();
		void ScrollCurrentCharacterDown();
		void SetHighscoreListComp(HighScoreListComponent* pHighscoreList);
		void Update() override;
		void SaveHighScore();

	private:
		void UpdateIndicatorPosition() const;


		std::vector<CharacterScrollComponent*> m_Character;
		GameObject*                            m_pUpIndicator{nullptr};
		GameObject*                            m_pDownIndicator{nullptr};
		HighScoreListComponent*                m_pHighScoreList{nullptr};
		int                                    m_CurrentlySelectedCharacter{0};
		const float                            m_InputCooldown{0.2f};
		float                                  m_CurrentCooldown{0.f};
		bool                                   m_InputOnCooldown{false};
		bool                                   m_IsSaved{false};
	};
}
