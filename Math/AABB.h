#ifndef AABB_H
#define AABB_H

#include "Ray.h"
#include <stdint.h>

class AABB
{
public:
	// minimum and maximum extent of the box
	Vector3 min, max;

	AABB();
	// a -> top back left of box, b -> bottom front right of box
	AABB(const Vector3 &a, const Vector3 &b);

	bool Hit(const Ray &ray, float &tMin, float &tMax) const;
	uint8_t GetLongestAxis() const;
	Vector3 GetCentroidPoint() const;
	AABB ExpandBoundingBox(const AABB &box);
	AABB GetSurroundingBox(const AABB &box0, const AABB& box1);
};

#endif