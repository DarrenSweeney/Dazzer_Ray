#include "Sampler.h"

float randF(float start, float end)
{
	static std::random_device rand_dev;
	static std::mt19937 generator(rand_dev());
	static std::uniform_real<float> distr(start, end);
	return distr(generator);
}

Vector3 RandomInUnitSphere()
{
	Vector3 point;

	do
	{
		point = 2.0f * Vector3(randF(-1.0f, 1.0f), randF(-1.0f, 1.0f), randF(-1.0f, 1.0f)) - Vector3(1.0f, 1.0f, 1.0f);
	} while (point.LengthSquared() >= 1.0f);

	return point;
}

Vector3 RandomInUnitDisk()
{
	Vector3 point;

	do
	{
		point = 2.0f * Vector3(randF(-1.0f, 1.0f), randF(-1.0f, 1.0f), 0.0f) - Vector3(1.0f, 1.0f, 0.0f);
	} while (Dot(point, point) >= 1.0f);

	return point;
}