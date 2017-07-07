#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Hitable.h"
#include <float.h>

/*
	@Note(Darren): Need to refacor this, might take out hitable and material, leaving it for testing
*/
class Triangle : public Hitable
{
public:
	Triangle();
	Triangle(Vector3 &_p1, Vector3 &_p2, Vector3 &_p3, Material *_material);

	bool Hit(const Ray &ray, float tMin, float tMax, HitRecord &hitRecord) const override;
	bool BoundingBox(float t0, float t1, AABB &box) const override;

private:
	Vector3 p1, p2, p3;
	Material *material;
};

#endif