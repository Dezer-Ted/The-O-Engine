#pragma once
#include <chrono>

#include "../../SceneObjects/GameObject.h"
#include <math.h>


namespace Utils
{
	enum class GameEvent {
		PlayerDied,
		PlayerGainedPoints,
		PlayerSpawn,
		DirectionChanged,
		MovementStopped,
		MovementStarted,
		Collision,
		AnimationEnded,
		PlayerSighted,
		TransitionState,
		EnemyDied,
		Explosion,
		InputDisconnected,
		ObjectDestroyed
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
		if(inputString.length() < length)
			return inputString;
		return inputString.substr(0, length);
	}

	inline float DegToRad(float deg)
	{
		return static_cast<float>(deg * (PI / 180));
	}
}
