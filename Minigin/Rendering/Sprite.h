#pragma once
#include <memory>
#include <SDL_rect.h>
#include <string>

#include "Texture2D.h"

namespace dae
{
	class Sprite {
	public:
		Sprite(const std::string& filePath, int numOfCols, int numOfRows);
		Sprite(const Sprite&) = delete;
		Sprite(Sprite&&) = delete;
		Sprite& operator=(const Sprite&) = delete;
		Sprite& operator=(Sprite&&) = delete;
		~Sprite() = default;
		Texture2D* GetTexture();
		int        m_TargetWidth{0};
		int        m_TargetHeight{0};
		int        m_NumberOfCols{0};
		int        m_NumberOfRows{0};
		int        m_SpriteWidth{0};
		int        m_SpriteHeight{0};
		int        m_CurrentCol{0};
		int        m_CurrentRow{0};
		SDL_Rect   m_SrcRect{};

	private:
		std::shared_ptr<dae::Texture2D> m_pTexture;
	};
}
