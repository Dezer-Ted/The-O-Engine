#pragma once

namespace dae
{
	class BaseComponent;
	class ColliderComponent;

	class ObserverEventData {
	public:
		ObserverEventData(dae::BaseComponent* component);
		ObserverEventData(const ObserverEventData&) = delete;
		ObserverEventData(ObserverEventData&&) = delete;
		ObserverEventData&  operator=(const ObserverEventData&) = delete;
		ObserverEventData&  operator=(ObserverEventData&&) = delete;
		virtual             ~ObserverEventData() = default;
		dae::BaseComponent* m_Component;
	};

	class CollisionEventData final : public ObserverEventData {
	public:
		CollisionEventData(BaseComponent* component, ColliderComponent* otherCollider);
		CollisionEventData(const CollisionEventData&) = delete;
		CollisionEventData(CollisionEventData&&) = delete;
		CollisionEventData& operator=(const CollisionEventData&) = delete;
		CollisionEventData& operator=(CollisionEventData&&) = delete;
		~CollisionEventData() override = default;
		ColliderComponent* m_OtherCollider;
	};
}
