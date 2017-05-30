#ifndef SPHERE_H
#define SPHERE_H

#include "..\Hitable.h"

class Sphere : Hitable
{
public:
	Sphere();
	Sphere(const Vector3 &_center, const float &_radius);

	bool Hit(const Ray &ray, float tMin, float tMax, HitRecord &hitRecord) const override;
	bool BoundingBox(float t0, float t1, AABB &box) const override;

private:
	float radius;
	Vector3 center;
};

#endif