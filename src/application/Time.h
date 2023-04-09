#pragma once
#include <chrono>

class Time {
public:
	Time();
	double deltaTime();
	void StartFrame();
	void EndFrame();
private:
	double prevStep = 0;
	std::chrono::high_resolution_clock::time_point frameTime;
};