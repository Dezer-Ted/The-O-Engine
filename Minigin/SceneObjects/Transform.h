#pragma once
#include <glm/glm.hpp>

namespace dae
{
	class GameObject;

	class Transform final {
	public:
		Transform(dae::GameObject* pOwner);
		Transform(const Transform&) = delete;
		Transform(Transform&&) = delete;
		Transform& operator=(const Transform&) = delete;
		Transform& operator=(Transform&&) = delete;
		~Transform() = default;

		glm::vec3        GetWorldPosition();
		const glm::vec3& GetLocalPosition() const { return m_LocalPosition; }
		void             SetLocalPosition(float x, float y, float z);
		void             SetLocalPosition(const glm::vec3& pos);
		void             SetAngleDeg(float angle);
		double           GetAngle() const; //angle in Deg

	private:
		glm::vec3   m_LocalPosition{};
		glm::vec3   m_WorldPosition{};
		GameObject* m_pOwner{nullptr};
		bool        m_PositionDirty{false};
		double      m_Angle{0};
		void        UpdateWorldPosition();
	};
}
