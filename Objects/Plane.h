#ifndef PLANE_H
#define PLANE_H

#include "Hitable.h"
#include "..\Materials\Material.h"

class Plane : public Hitable
{
public:
	Plane(Vector3 &position, Vector3 &normal, Material *material);
	~Plane();

	bool Hit(const Ray &ray, float tMin, float tMax, HitRecord &hitRecord) const override;
	bool BoundingBox(float t0, float t1, AABB &box) const override;

private:
	Vector3 position;
	Vector3 normal;
	Material *material;
};

#endif