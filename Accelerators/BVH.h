#ifndef BVH_H
#define BVH_H

#include "..\Objects\Triangle.h"
#include "..\Objects\Hitable.h"

class BVH : public Hitable
{
public:
	BVH();
	BVH(Hitable **list, int size);
	~BVH();

	bool Hit(const Ray &ray, float tMin, float tMax, HitRecord &rec) const override;
	bool BoundingBox(float t0, float t1, AABB &box) const override;

private:
	Hitable **hitableList;
	int listSize;
	// The bounding box surrounding all hitables
	AABB boundingBox;

};

#endif