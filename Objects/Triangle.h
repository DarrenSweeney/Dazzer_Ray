#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Hitable.h"
#include <float.h>

class Triangle
{
public:
	Triangle();
	Triangle(Vector3 &_p1, Vector3 &_p2, Vector3 &_p3);

	bool Hit(const Ray &ray, float tMin, float tMax, HitRecord &hitRecord) const;
	bool BoundingBox(float t0, float t1, AABB &box) const;

private:
	Vector3 p1, p2, p3;
};

#endif