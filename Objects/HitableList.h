#ifndef HITABLE_LIST_H
#define HITABLE_LIST_H

#include "Hitable.h"

class HitableList : public Hitable
{
public:
	HitableList();
	HitableList(Hitable **list, int size);
	~HitableList();

	bool Hit(const Ray &ray, float tMin, float tMax, HitRecord &rec) const override;
	bool BoundingBox(float t0, float t1, AABB &box) const override;

private:
	Hitable **hitableList;
	int listSize;
};

#endif