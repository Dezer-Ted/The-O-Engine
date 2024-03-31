#include "Sprite.h"

#include "../Engine/ResourceManager.h"

dae::Sprite::Sprite(const std::string& filePath, int numOfCols, int numOfRows)
{
	m_NumberOfCols = numOfCols;
	m_NumberOfRows = numOfRows;
	m_pTexture = dae::ResourceManager::GetInstance().LoadTexture(filePath);
	const auto size = m_pTexture->GetSize();
	m_SpriteWidth = size.x / numOfCols;
	m_SpriteHeight = size.y / numOfRows;
	m_TargetHeight = m_SpriteHeight;
	m_TargetWidth = m_SpriteWidth;
	m_SrcRect.h = m_SpriteHeight;
	m_SrcRect.w = m_SpriteWidth;
}

dae::Texture2D* dae::Sprite::GetTexture()
{
	return m_pTexture.get();
}
