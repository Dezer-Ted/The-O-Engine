#include "SpriteComponent.h"

#include "../Engine/DeltaTime.h"
#include "../Rendering/Renderer.h"

#include "../Engine/ResourceManager.h"
#include "../SceneObjects/GameObject.h"
#include "../Rendering/Sprite.h"

dae::SpriteComponent::SpriteComponent(GameObject* pParent)
	: BaseComponent(pParent)

{

}

dae::SpriteComponent::~SpriteComponent()
{
}

void dae::SpriteComponent::Render()
{
	if(m_pCurrentSprite->GetTexture() == nullptr) return;

	const auto& pos{GetParent()->GetTransform().GetWorldPosition()};
	Renderer::GetInstance().RenderTexture(*m_pCurrentSprite->GetTexture(), pos.x, pos.y, static_cast<float>(m_pCurrentSprite->m_SpriteWidth) * m_Scale,
	                                      static_cast<float>(m_pCurrentSprite->m_SpriteHeight) * m_Scale, &m_pCurrentSprite->m_SrcRect);
}

void dae::SpriteComponent::Update()
{
	if(!m_IsUpdating)
		return;
	m_CurrentTime += Singleton<DeltaTime>::GetInstance().GetDeltaTime();
	if(m_CurrentTime >= m_RefreshRate)
	{
		UpdateSrcRect();
		m_CurrentTime = 0.f;
	}
}

void dae::SpriteComponent::AddSprite(int numOfCols, int numOfRows, const std::string& filePath,const std::string& animationName)
{
	m_SpriteMap.insert(std::make_pair(animationName, std::make_unique<Sprite>(filePath, numOfCols, numOfRows)));
	SwitchToSprite(animationName);
}

void dae::SpriteComponent::SetScale(float scale)
{
	m_Scale = scale;
}

void dae::SpriteComponent::SwitchToSprite(const std::string& animationName)
{
	auto newAnimation = m_SpriteMap.find(animationName);
	if(newAnimation == m_SpriteMap.end())
	{
		std::cout << "No animation with that name\n";
		return;
	}

	m_pCurrentSprite = newAnimation->second.get();
	
}

void dae::SpriteComponent::ShouldUpdate(bool updateSprite)
{
	m_IsUpdating = updateSprite;
}

dae::Sprite* dae::SpriteComponent::GetCurrentSprite() const
{
	return m_pCurrentSprite;
}

float dae::SpriteComponent::GetScale() const
{
	return m_Scale;
}

void dae::SpriteComponent::UpdateSrcRect()
{
	++m_pCurrentSprite->m_CurrentCol;
	if(m_pCurrentSprite->m_CurrentCol + 1 > m_pCurrentSprite->m_NumberOfCols)
	{
		m_pCurrentSprite->m_CurrentCol = 0;
		++m_pCurrentSprite->m_CurrentRow;
	}
	if(m_pCurrentSprite->m_CurrentRow + 1 > m_pCurrentSprite->m_NumberOfRows)
	{
		m_pCurrentSprite->m_CurrentRow = 0;
	}
	m_pCurrentSprite->m_SrcRect.x = m_pCurrentSprite->m_SpriteWidth * m_pCurrentSprite->m_CurrentCol;
	m_pCurrentSprite->m_SrcRect.y = m_pCurrentSprite->m_SpriteHeight * m_pCurrentSprite->m_CurrentRow;
}
