#pragma once
#include <memory>
#include "Minigin.h"

class Time {
public:
	Time();
	Time(const Time& time) = delete;
	Time(Time&& time) = delete;
	Time& operator=(const Time& time) = delete;
	Time& operator=(Time&& time) = delete;
	~Time() = default;
	float GetDeltaTime();
private:
	float m_DeltaTime {};
	void SetDeltaTime(float deltaT);
	friend class dae::Minigin;
	
};
