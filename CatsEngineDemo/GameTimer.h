#pragma once
#include <chrono>

using _Clock = std::chrono::high_resolution_clock;
using time_point = std::chrono::time_point<_Clock>;
using duration = std::chrono::duration<float>;

/*
 * TODO:
 * Add Fixed frame delta for physics interactions
 * Pause Timer when the game's not running
 *		(not focused or something like that)
 */
class GameTimer
{
private:
	time_point startTime;
	time_point lastTime;
	time_point thisTime;

	// cache
	duration fullTime;
	duration frameTime;

public:
	GameTimer();
	~GameTimer();

	void Setup();
	void Update();

	inline float GetDelta() { return frameTime.count(); }
	inline float GetTime() { return fullTime.count(); }
};