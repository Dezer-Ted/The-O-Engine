#pragma once
#include <glm/vec3.hpp>

#include "BaseComponent.h"
class GameObject;

namespace dae
{
	class EncircleComponent final : public dae::BaseComponent {
	public:
		EncircleComponent(GameObject* pParent);
		EncircleComponent(const EncircleComponent&) = delete;
		EncircleComponent(EncircleComponent&&) = delete;
		EncircleComponent& operator=(const EncircleComponent&) = delete;
		EncircleComponent& operator=(EncircleComponent&&) = delete;
		~EncircleComponent() = default;
		void Update() override;
		void SetPivot(const glm::vec3& pivot);
		void SetRadius(float radius);

	private:
		glm::vec3   m_Pivot{0, 0, 0};
		float       m_Radius{};
		float       m_CurrentRotationDEG{0.f};
		const float m_DegreesPerSecond{360.f};
	};
}

