#pragma once
#include <memory>

#include "BaseComponent.h"
#include "TextComponent.h"

namespace dae
{
	class FPSComponent final : public BaseComponent {
	public:
		FPSComponent(GameObject* pParent);
		void Update() override;
		~FPSComponent() override;

	private:
		int            m_FPSCounter{};
		float          m_ElapsedTime{};
		const float    m_TimeSpan{1.f};
		float          m_LastFPS{};
		TextComponent* m_TextComponent;
	};
}
