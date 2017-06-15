#ifndef HITABLE_H
#define HITABLE_H

#include "HitRecord.h"
#include "..\Math\Ray.h"
#include "..\Math\AABB.h"

class Hitable
{
public:
	virtual bool Hit(const Ray &ray, HitRecord &hitRecord) const = 0;
	virtual bool BoundingBox(float t0, float t1, AABB &box) const = 0;
};

#endif