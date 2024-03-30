#pragma once
#include <chrono>

#include "GameObject.h"
#include "Time.h"
#include "Singleton.h"
#include <math.h>
#include <../steamworks/public/steam/steam_api.h>


namespace Utils
{
	enum GameEvent {
		PlayerDied,
		PlayerGainedPoints,
		PlayerSpawn,
		DirectionChanged,
		MovementStopped,
		MovementStarted
	};


	const double PI{3.1415926535f};

	constexpr auto floatToDuration(const float time)
	{
		using namespace std::chrono;
		using fsec = duration<float>;
		return round<milliseconds>(fsec{time});
	}

	inline float Round(float input)
	{
		const float value = static_cast<float>(static_cast<int>(input * 100 + 0.5f));
		return static_cast<float>(value) / 100.f;
	}

	inline std::string TruncateString(const std::string& inputString, unsigned int length)
	{
		if(inputString.length() < length) return inputString;
		return inputString.substr(0, length);
	}

	inline float DegToRad(float deg)
	{
		return static_cast<float>(deg * (PI / 180));
	}
}
