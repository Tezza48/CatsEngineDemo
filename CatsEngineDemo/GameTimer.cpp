#include "GameTimer.h"



GameTimer::GameTimer()
{
}


GameTimer::~GameTimer()
{
}

void GameTimer::Setup()
{
	lastTime = thisTime = startTime = std::chrono::high_resolution_clock::now();
}

void GameTimer::Update()
{
	lastTime = thisTime;
	thisTime = _Clock::now();

	// cache durations for this tick
	fullTime = _Clock::now() - startTime;
	frameTime = thisTime - lastTime;
}
