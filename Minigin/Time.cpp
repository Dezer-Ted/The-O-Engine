#include "Time.h"

Time::Time()
{
	
}

float Time::GetDeltaTime()
{
	return m_DeltaTime;
}

void Time::SetDeltaTime(float deltaT)
{
	m_DeltaTime = deltaT;
}
