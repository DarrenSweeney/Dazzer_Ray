#ifndef SAMPLER_H
#define SAMPLER_H

#include <random>
#include "Math\Vector3.h" 

float randF(float start, float end);

Vector3 RandomInUnitSphere();
Vector3 RandomInUnitDisk();

#endif