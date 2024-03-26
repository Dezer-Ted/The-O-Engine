#include "SpriteComponent.h"

#include "../DeltaTime.h"
#include "../Renderer.h"

#include "../ResourceManager.h"
#include "../GameObject.h"

dae::SpriteComponent::SpriteComponent(GameObject* pParent)
	: BaseComponent(pParent)

{

}

void dae::SpriteComponent::Render()
{
	if(m_pTexture == nullptr) return;

	const auto& pos{GetParent()->GetTransform().GetWorldPosition()};
	Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y, &m_SrcRect);
}

void dae::SpriteComponent::Update()
{
	m_CurrentTime += Singleton<DeltaTime>::GetInstance().GetDeltaTime();
	if(m_CurrentTime >= m_RefreshRate)
	{
		UpdateSrcRect();
		m_CurrentTime = 0.f;
	}
}

void dae::SpriteComponent::InitComponent(int numOfCols, int numOfRows, const std::string& filePath)
{
		m_NumberOfCols = numOfCols;
		m_NumberOfRows = numOfRows;
		m_pTexture = ResourceManager::GetInstance().LoadTexture(filePath);
    	const auto size = m_pTexture->GetSize();
    	m_SpriteWidth = size.x / numOfCols;
    	m_SpriteHeight = size.y / numOfRows;
    	m_SrcRect.h = m_SpriteHeight;
    	m_SrcRect.w = m_SpriteWidth;

}

void dae::SpriteComponent::UpdateSrcRect()
{
	++m_CurrentCol;
	if(m_CurrentCol + 1 > m_NumberOfCols)
	{
		m_CurrentCol = 0;
		++m_CurrentRow;

	}
	if(m_CurrentRow + 1 > m_NumberOfRows)
	{
		m_CurrentRow = 0;
	}
	m_SrcRect.x = m_SpriteWidth * m_CurrentCol;
	m_SrcRect.y = m_SpriteHeight * m_CurrentRow;

}
