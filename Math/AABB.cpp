#include "AABB.h"

AABB::AABB() { }

AABB::AABB(const Vector3 &a, const Vector3 &b)
	: min(a), max(b)
{

}

bool AABB::Hit(const Ray &ray, float tMin, float tMax) const
{
	for (int a = 0; a < 3; a++) 
	{
		float t0 = fmin((min[a] - ray.Origin()[a]) / ray.Direction()[a],
			(max[a] - ray.Origin()[a]) / ray.Direction()[a]);
		float t1 = fmax((min[a] - ray.Origin()[a]) / ray.Direction()[a],
			(max[a] - ray.Origin()[a]) / ray.Direction()[a]);

		tMin = fmax(t0, tMin);
		tMax = fmin(t1, tMax);

		if (tMax <= tMin)
			return false;
	}

	return true;
}

AABB AABB::GetSurroundingBox(AABB &box0, AABB& box1)
{
	Vector3 min(fminf(box0.min.x, box1.min.x), fminf(box0.min.y, box1.min.y), fminf(box0.min.z, box1.min.z));
	Vector3 max(fmaxf(box0.max.x, box1.max.x), fmaxf(box0.max.y, box1.max.y), fmaxf(box0.max.z, box1.max.z));

	return AABB(min, max);
}