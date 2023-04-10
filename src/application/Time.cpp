#include "Time.h"

Time::Time()
{
}

float Time::deltaTime()
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
	prevStep = std::chrono::duration<float>(std::chrono::high_resolution_clock::now() - frameTime).count();
}
