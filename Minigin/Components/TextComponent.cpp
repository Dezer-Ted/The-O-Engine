#include "TextComponent.h"
#include "../Rendering/Renderer.h"

#include <SDL_ttf.h>
#include <utility>
#include "../Rendering/Texture2D.h"
#include "TextureComponent.h"

dae::TextComponent::TextComponent(GameObject* pParent):
	BaseComponent(pParent),
	m_Color{SDL_Color{255, 255, 255, 255}}
{
	m_TextureComponent = pParent->AddComponent<TextureComponent>();
}

dae::TextComponent::~TextComponent()
{
}

void dae::TextComponent::SetText(const std::string& text, std::shared_ptr<Font> font, const SDL_Color& color)
{
	m_Text = text;
	m_pFont = std::move(font);
	m_Color = color;
	m_TextDirtyFlag = true;
}

void dae::TextComponent::SetText(const std::string& text)
{
	if(m_pFont == nullptr)
	{
		std::cout << "Text Component does not have a font ";
		return;
	}
	m_Text = text;
	m_TextDirtyFlag = true;
}

void dae::TextComponent::Render()
{

}

void dae::TextComponent::Update()
{
	if(m_TextDirtyFlag)
		UpdateText();
}

void dae::TextComponent::UpdateText()
{
	m_TextDirtyFlag = false;
	const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), m_Color);
	if(surf == nullptr)
	{
		throw std::runtime_error(std::string{"Render Text Failed"} + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
	if(texture == nullptr)
	{
		throw std::runtime_error(std::string{"Create text texture from surface failed: "} + SDL_GetError());
	}
	SDL_FreeSurface(surf);
	m_TextureComponent->SetTexture(std::make_shared<Texture2D>(texture));
}
