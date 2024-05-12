#pragma once
#include <map>
#include <memory>
#include <SDL_rect.h>
#include <string>

#include "BaseComponent.h"
#include "../Engine/DesignPatterns/Observable.h"


namespace dae
{
	class Sprite;

	class SpriteComponent final : public BaseComponent, public Observable {
	public:
		SpriteComponent(GameObject* pParent);
		SpriteComponent(const SpriteComponent&) = delete;
		SpriteComponent(SpriteComponent&&) = delete;
		SpriteComponent operator=(const SpriteComponent&) = delete;
		SpriteComponent operator=(SpriteComponent&&) = delete;
		~SpriteComponent() override;
		void    Render() override;
		void    Update() override;
		void    AddSprite(int numOfCols, int numOfRows, const std::string& filePath, const std::string& animationName);
		void    SetScale(float scale);
		void    SwitchToSprite(const std::string& animationName);
		void    ShouldUpdate(bool updateSprite);
		Sprite* GetCurrentSprite() const;
		float   GetScale() const;

	private:
		void UpdateSrcRect();

		bool                                           m_IsUpdating{true};
		std::map<std::string, std::unique_ptr<Sprite>> m_SpriteMap;
		float                                          m_Scale{1};
		Sprite*                                        m_pCurrentSprite;
		const float                                    m_RefreshRate{1.f / 6.f};
		float                                          m_CurrentTime{0};
	};
}
