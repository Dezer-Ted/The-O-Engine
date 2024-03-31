#pragma once
#include <vector>


namespace dae
{
	class ColliderComponent;

	class CollisionCheck {
	public:
		CollisionCheck() = default;
		CollisionCheck(const CollisionCheck&) = delete;
		CollisionCheck(CollisionCheck&&) = delete;
		CollisionCheck& operator=(const CollisionCheck&) = delete;
		CollisionCheck& operator=(CollisionCheck&&) = delete;
		~CollisionCheck() = default;
		void AddCollider(ColliderComponent* newCollider);
		void RemoveCollider(ColliderComponent* newCollider);
		void CheckAllColliders();

	private:
		std::vector<ColliderComponent*> m_Colliders;
		std::vector<ColliderComponent*> m_UncheckedColliders;

		void CheckCollision(ColliderComponent* pFirstCollider, ColliderComponent* pSecondCollider);
	};
}
