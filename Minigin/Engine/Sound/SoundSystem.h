#pragma once

class SoundSystem {
public:
	virtual      ~SoundSystem() = default;
	virtual void Play() = 0;
};
