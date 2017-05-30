#ifndef AABB_H
#define AABB_H

#include "Ray.h"

class AABB
{
public:
	// minimum and maximum extent of the box
	Vector3 min, max;

	AABB();
	// a -> top back left of box, b -> bottom front right of box
	AABB(const Vector3 &a, const Vector3 &b);

	bool Hit(const Ray &ray, float tMin, float tMax) const;
	AABB GetSurroundingBox(AABB &box0, AABB& box1);
};

#endif
