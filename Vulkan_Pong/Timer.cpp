#include "Timer.h"

Timer::Timer(double seconds):
	seconds(seconds),
	isRunning(false)
{

}

void Timer::Configure(double secs)
{
	seconds = secs;
}

void Timer::Start()
{
	currentStartTime = std::chrono::high_resolution_clock::now();
	isRunning = true;
}

void Timer::StopAndReset()
{
	isRunning = false;
}

bool Timer::IsFinished()
{
	auto now = std::chrono::high_resolution_clock::now();
	return isRunning && std::chrono::duration<float, std::chrono::seconds::period>(now - currentStartTime).count() > seconds;
}

double Timer::GetElapsedTime()
{
	if (isRunning) {
		auto now = std::chrono::high_resolution_clock::now();
		return std::chrono::duration<float, std::chrono::seconds::period>(now - currentStartTime).count();
	}
	return 0;
}

double Timer::GetRemainingTime()
{
	if (isRunning) {
		auto now = std::chrono::high_resolution_clock::now();
		return seconds - std::chrono::duration<float, std::chrono::seconds::period>(now - currentStartTime).count();
	}
	return -1;
}
