#ifndef SPHERE_H
#define SPHERE_H

#include "..\Objects\Hitable.h"
#include <float.h>

class Sphere : public Hitable
{
public:
	Sphere();
	Sphere(const Vector3 &_center, const float &_radius, Material *material);
	~Sphere();

	bool Hit(const Ray &ray, HitRecord &hitRecord) const override;
	bool BoundingBox(float t0, float t1, AABB &box) const override;

private:
	float radius;
	Vector3 center;
	Material *material;
};

#endif