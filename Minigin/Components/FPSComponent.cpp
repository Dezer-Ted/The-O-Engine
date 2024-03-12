#include "FPSComponent.h"

#include "../ResourceManager.h"
#include "../Time.h"
#include "../Utils.h"

dae::FPSComponent::FPSComponent(GameObject* pParent) : BaseComponent(pParent)
{
	m_TextComponent = pParent->AddComponent<TextComponent>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf",36);
	m_TextComponent->SetText("1",font,{255,255,255,255});
}

void dae::FPSComponent::Update()
{
	const float deltaT{dae::Singleton<Time>::GetInstance().GetDeltaTime()};
	m_ElapsedTime += deltaT;
	++m_FPSCounter;
	if(m_ElapsedTime >= m_TimeSpan)
	{
		const float fps {static_cast<float>(m_FPSCounter) / m_ElapsedTime};
		m_FPSCounter = 0;
		m_ElapsedTime -= m_TimeSpan;
		if(abs(fps-m_LastFPS) < FLT_EPSILON)
			return;
		std::stringstream ss;
		ss << std::fixed << std::setprecision(1) << fps << "FPS";
		m_TextComponent->SetText(ss.str());
		m_LastFPS = fps;
	}
	
}

dae::FPSComponent::~FPSComponent()
{
	GetParent()->RemoveComponentByClass<TextComponent>();
}
