#pragma once
#include <vector>
#include <glm/vec2.hpp>

#include "Components/BaseComponent.h"


namespace dae
{
	class TextComponent;
	class GameObject;

	class CharacterScrollComponent final : public dae::BaseComponent {
	public:
		CharacterScrollComponent(GameObject* pParent);
		CharacterScrollComponent(const CharacterScrollComponent& other) = delete;
		CharacterScrollComponent(CharacterScrollComponent&& other) noexcept = delete;
		CharacterScrollComponent& operator=(const CharacterScrollComponent& other) = delete;
		CharacterScrollComponent& operator=(CharacterScrollComponent&& other) noexcept = delete;
		~CharacterScrollComponent() override = default;
		void IncrementCharacter();
		void DecrementCharacter();
		glm::vec2 GetPosition() const;
		char GetCurrentCharacter() const;
	private:
		std::vector<char> m_Characters{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
			'X', 'Y', 'Z'};
		int            m_CurrentCharacter{0};
		TextComponent* m_pTextComp{nullptr};
		
	};
}
