#include "Time.h"

Time::Time()
{
}

double Time::deltaTime()
{
	//auto currentStep = std::chrono::high_resolution_clock::now();
	//return std::chrono::duration_cast<std::chrono::seconds>(currentStep - prevStep).count();
	return prevStep;
}

void Time::StartFrame()
{
	frameTime = std::chrono::high_resolution_clock::now();
}

void Time::EndFrame()
{
	prevStep = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - frameTime).count();
}
