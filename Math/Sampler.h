#ifndef SAMPLER_H
#define SAMPLER_H

#include <random>
#include "Vector3.h" 

float randF(float start = 0.0f, float end = 1.0f);

Vector3 RandomInUnitSphere();
Vector3 RandomInUnitDisk();

#endif