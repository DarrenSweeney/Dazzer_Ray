#include <WinBase.h>
#include <cstdint>

#define PROFILE(name) AutoProfile p(name)

struct AutoProfile
{
	AutoProfile(const char *_name)
	{
		name = _name;
		QueryPerformanceCounter(startTime);
	}

	~AutoProfile()
	{
		LARGE_INTEGER *endTime; 
		QueryPerformanceCounter(endTime);
		//LARGE_INTEGER elapsedTime = *endTime - *startTime;
	}

	const char *name;
	LARGE_INTEGER *startTime;
};
