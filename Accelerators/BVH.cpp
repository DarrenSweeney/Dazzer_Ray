#include "BVH.h"

BVH::BVH() { }

BVH::BVH(std::vector<Hitable*> *_primsVector)
	: primsVector(_primsVector)
{
	// Calculate the bounding box surround the whole list of hitables
	primsVector->at(0)->BoundingBox(0.0f, 0.0f, boundingBox);	// Top level bound
	AABB box;
	for (size_t i = 1; i < primsVector->size(); i++)
	{
		primsVector->at(i)->BoundingBox(0.0f, 0.0f, box);
		boundingBox = boundingBox.ExpandBoundingBox(box);
	}
}

BVH::~BVH()
{
	for (Hitable *hitable : *primsVector)
		delete hitable;
}

bool BVH::RayTraveral(std::vector<Hitable*> *prims, const Ray & ray,
	float tMin, float tMax, HitRecord & rec) const
{
	

	return false;
}

bool BVH::Hit(const Ray &ray, float tMin, float tMax, HitRecord &rec) const
{
	if (RayTraveral(primsVector, ray, tMin, tMax, rec))
		return true;
	else
		return false;
}

bool BVH::BoundingBox(float t0, float t1, AABB &box) const
{
	box = boundingBox;

	return false;
}