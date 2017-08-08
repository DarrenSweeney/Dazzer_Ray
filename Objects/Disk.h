#ifndef DISK_H
#define DISK_H

#include "Hitable.h"
#include "..\Materials\Material.h"

class Disk : public Hitable
{
public:
	Disk(Vector3 &position, Vector3 &normal, float radius, Material *material);

	bool Hit(const Ray &ray, float tMin, float tMax, HitRecord &hitRecord) const override;
	bool BoundingBox(float t0, float t1, AABB &box) const override;

private:
	Vector3 position;
	Vector3 normal;
	float radius;
	Material *material;
};

#endif