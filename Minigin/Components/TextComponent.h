#pragma once
#include <SDL_pixels.h>

#include "BaseComponent.h"
#include "../Font.h"
#include "../GameObject.h"

namespace dae
{
	class TextComponent final : public dae::BaseComponent {
	public:
		TextComponent(GameObject* parent);
		TextComponent(const TextComponent& textComponent) = delete;
		TextComponent(TextComponent&& textComponent) = delete;
		TextComponent& operator=(const TextComponent& textComponent) = delete;
		TextComponent& operator=(TextComponent&& textComponent) = delete;
		~TextComponent() override;
		void SetText(const std::string& text, std::shared_ptr<Font> font, const SDL_Color& color);
		void SetText(const std::string& text);
		void Render() override;
		void Update() override;

		void LateUpdate() override
		{
		}

	private:
		std::string                m_Text;
		SDL_Color                  m_Color;
		std::shared_ptr<Font>      m_pFont;
		std::shared_ptr<Texture2D> m_pTexture;
		void                       UpdateText();
		TextureComponent*          m_TextureComponent;
		bool                       m_TextDirtyFlag{false};
	};
}
