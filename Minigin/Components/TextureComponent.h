#pragma once
#include <memory>
#include <Windows.h>
#include <string>
#include "BaseComponent.h"
class GameObject;

namespace dae
{
	class Texture2D;
	
	class TextureComponent final : public BaseComponent {
	public:
		TextureComponent(GameObject* parentObject);
		TextureComponent(const TextureComponent& textureComponent) = delete;
		TextureComponent(TextureComponent&& textureComponent) = delete;
		TextureComponent& operator=(const TextureComponent& textureComponent) = delete;
		TextureComponent& operator=(TextureComponent&& textureComponent) = delete;
		~TextureComponent() override;
		void Render() override;
		void SetTexture(const std::string& texturePath);
		void SetTexture(std::shared_ptr<Texture2D> texture);

	private:
		void                       Update() override;
		void                       LateUpdate() override;
		std::shared_ptr<Texture2D> m_Texture;
	};
}

