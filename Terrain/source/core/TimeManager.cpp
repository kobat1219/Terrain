#include "TimeManager.h"

void Time::Init()
{
	QueryPerformanceFrequency(&frequency);
	current_time.QuadPart = 0;
	last_time.QuadPart = 0;
	delta_time = 0;
}

void Time::Update()
{
	QueryPerformanceCounter(&current_time);

	delta_time = current_time.QuadPart - last_time.QuadPart;

	last_time = current_time;
}

double Time::DeltaTime()
{
	return (double)delta_time/(double)frequency.QuadPart;
}
