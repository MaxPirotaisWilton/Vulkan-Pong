#pragma once
#include <chrono>

class Timer
{
private:
	double seconds;
	bool isRunning;
	std::chrono::steady_clock::time_point currentStartTime;

public: 
	Timer(double seconds);

	double GetSeconds() { return seconds; };

	bool IsRunning() const { return isRunning; }
	bool IsFinished();

	double GetElapsedTime();
	double GetRemainingTime();

	void Configure(double seconds);
	void Start();
	void StopAndReset();
};

