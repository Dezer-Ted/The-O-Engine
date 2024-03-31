#pragma once
#include <SDL_rect.h>

#include "BaseComponent.h"
#include "../Engine/DesignPatterns/Observable.h"

namespace dae
{
	class ColliderComponent final : public BaseComponent, public Observable {
	public:
		ColliderComponent(GameObject* pParent);
		ColliderComponent(const ColliderComponent&) = delete;
		ColliderComponent(ColliderComponent&&) = delete;
		ColliderComponent& operator=(const ColliderComponent&) = delete;
		ColliderComponent& operator=(ColliderComponent&&) = delete;
		~ColliderComponent() override = default;

		SDL_Rect GetBounds() const;
		void     SetBounds(const SDL_Rect& bounds);
		void     AdjustBoundsToSpriteSize();
		void     CollidedWith(ColliderComponent* other);
		void     Update() override;
		std::string GetParentTag() const;
		
	private:
		SDL_Rect m_Bounds{0, 0, 0, 0};
	};
}
