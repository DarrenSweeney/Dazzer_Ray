#ifndef HITABLE_LIST_H
#define HITABLE_LIST_H

#include <vector>
#include "Hitable.h"

class HitableList : public Hitable
{
public:
	HitableList();
	~HitableList();

	void Add(Hitable *hitable);

	bool Hit(const Ray &ray, float tMin, float tMax, HitRecord &rec) const override;
	bool BoundingBox(float t0, float t1, AABB &box) const override;

private:
	std::vector<Hitable*> hitables;
};

#endif