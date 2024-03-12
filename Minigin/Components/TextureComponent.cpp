#include "TextureComponent.h"

#include "../GameObject.h"
#include "../Renderer.h"
#include "../ResourceManager.h"
#include "../Texture2D.h"
dae::TextureComponent::TextureComponent(GameObject* parentObject) : BaseComponent(parentObject)
{
}

void dae::TextureComponent::SetTexture(const std::string& texturePath)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(texturePath);
}

void dae::TextureComponent::SetTexture(std::shared_ptr<Texture2D> texture)
{
	if (texture == nullptr)
		return;
	m_Texture = texture;
}

void dae::TextureComponent::Update()
{
}

void dae::TextureComponent::LateUpdate()
{
}

void dae::TextureComponent::Render()
{
	if (m_Texture == nullptr)
		return;
	const auto& pos{ GetParent()->GetTransform().GetWorldPosition() };
	Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}

dae::TextureComponent::~TextureComponent()
{

}

