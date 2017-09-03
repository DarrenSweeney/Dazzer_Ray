#include <time.h> 
#include <stdio.h>

#ifndef PROFILE_H
#define PROFILE_H

#define PROFILE(name) AutoProfile p(name)

struct AutoProfile
{
	AutoProfile(const char *_name)
	{
		name = _name;
		start = clock();
	}

	~AutoProfile()
	{
		duration = (clock() - start) / (double)CLOCKS_PER_SEC;
		printf("Profile of %s took %f\n", name, duration);
	}

	const char *name;
	clock_t start;
	double duration;
};

#endif PROFILE_H