#include "BVH.h"

BVH::BVH() { }

BVH::BVH(Hitable **list, int size)
	: hitableList(list), listSize(size)
{
	// Calculate the bounding box surround the whole list of hitables
	hitableList[0]->BoundingBox(0.0f, 0.0f, boundingBox);
	AABB box;
	for (int i = 1; i < listSize; i++)
	{
		hitableList[i]->BoundingBox(0.0f, 0.0f, box);
		boundingBox = boundingBox.ExpandBoundingBox(box);
	}
}

BVH::~BVH()
{
	delete[] hitableList;
}

bool BVH::Hit(const Ray &ray, float tMin, float tMax, HitRecord &rec) const
{
	HitRecord tempRecord;
	bool hitAnything = false;
	float closestSoFar = tMax;

	if (boundingBox.Hit(ray, tMin, tMax))
	{
		for (int i = 0; i < listSize; i++)
		{
			if (hitableList[i]->Hit(ray, tMin, closestSoFar, tempRecord))
			{
				hitAnything = true;
				closestSoFar = tempRecord.t;
				rec = tempRecord;
			}
		}
	}

	return hitAnything;
}

bool BVH::BoundingBox(float t0, float t1, AABB &box) const
{
	box = boundingBox;

	return false;
}