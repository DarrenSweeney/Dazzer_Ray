#include "HitableList.h"

// @Todo(Darren): Remove this class when i implement BVH
HitableList::HitableList() { }

HitableList::~HitableList()
{
	for (Hitable *hitable : hitables)
		delete hitable;
}

void HitableList::Add(Hitable *hitable)
{
	hitables.push_back(hitable);
}

bool HitableList::Hit(const Ray &ray, float tMin, float tMax, HitRecord &rec) const
{
	bool hitAnything = false;
	float closestSoFar = tMax;

	for (size_t i = 0; i < hitables.size(); i++)
	{
		if (hitables[i]->Hit(ray, tMin, closestSoFar, rec))
		{
			hitAnything = true;
			closestSoFar = rec.t;
		}
	}

	return hitAnything;
}

bool HitableList::BoundingBox(float t0, float t1, AABB &box) const
{
	if (hitables.size() < 1)
		return false;

	AABB tempBox;
	bool firstTrue = hitables[0]->BoundingBox(t0, t1, tempBox);
	if (!firstTrue)
		return false;
	else
		box = tempBox;

	for (size_t i = 1; i < hitables.size(); i++)
	{
		if (hitables[0]->BoundingBox(t0, t1, box))
			box = box.GetSurroundingBox(box, tempBox);
		else
			return false;
	}

	return true;
}