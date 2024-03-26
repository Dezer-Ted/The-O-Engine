#pragma once
#include <memory>
#include <SDL_rect.h>
#include <string>

#include "BaseComponent.h"
#include "../Texture2D.h"

namespace dae
{
	class SpriteComponent final : public BaseComponent {
	public:
		SpriteComponent(GameObject* pParent);
		SpriteComponent(const SpriteComponent&) = delete;
		SpriteComponent(SpriteComponent&&) = delete;
		SpriteComponent operator=(const SpriteComponent&) = delete;
		SpriteComponent operator=(SpriteComponent&&) = delete;
		~SpriteComponent() override = default;
		void Render() override;
		void Update() override;
		void InitComponent(int numOfCols, int numOfRows, const std::string& filePath);

	private:
		void UpdateSrcRect();

		int                        m_NumberOfCols{0};
		int                        m_NumberOfRows{0};
		int                        m_SpriteWidth{0};
		int                        m_SpriteHeight{0};
		int                        m_CurrentCol{0};
		int                        m_CurrentRow{0};
		std::shared_ptr<Texture2D> m_pTexture;
		SDL_Rect                   m_SrcRect;
		const float                m_RefreshRate{1.f / 12.f};
		float                      m_CurrentTime{0};
	};
}
