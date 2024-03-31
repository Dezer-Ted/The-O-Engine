#pragma once
#include <memory>
#include "Minigin.h"

class DeltaTime {
public:
	DeltaTime();
	DeltaTime(const DeltaTime& time) = delete;
	DeltaTime(DeltaTime&& time) = delete;
	DeltaTime& operator=(const DeltaTime& time) = delete;
	DeltaTime& operator=(DeltaTime&& time) = delete;
	~DeltaTime() = default;
	float GetDeltaTime();
private:
	float m_DeltaTime {};
	void SetDeltaTime(float deltaT);
	friend class dae::Minigin;
	
};
