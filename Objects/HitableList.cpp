#include "HitableList.h"

HitableList::HitableList() { }

HitableList::~HitableList()
{
	delete[] hitableList;
}

HitableList::HitableList(Hitable **list, int size)
	:	hitableList(list), listSize(size)
{
	
}

bool HitableList::Hit(const Ray &ray, float tMin, float tMax, HitRecord &rec) const
{
	HitRecord tempRecord;
	bool hitAnything = false;
	float closestSoFar = tMax;
	for (int i = 0; i < listSize; i++)
	{
		if (hitableList[i]->Hit(ray, tMin, closestSoFar, tempRecord))
		{
			hitAnything = true;
			closestSoFar = tempRecord.t;
			rec = tempRecord;
		}
	}

	return hitAnything;
}

bool HitableList::BoundingBox(float t0, float t1, AABB &box) const
{
	if (listSize < 1)
		return false;

	AABB tempBox;
	bool firstTrue = hitableList[0]->BoundingBox(t0, t1, tempBox);
	if (!firstTrue)
		return false;
	else
		box = tempBox;

	for (int i = 1; i < listSize; i++)
	{
		if (hitableList[0]->BoundingBox(t0, t1, box))
			box = box.GetSurroundingBox(box, tempBox);
		else
			return false;
	}

	return true;
}