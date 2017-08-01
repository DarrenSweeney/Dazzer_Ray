#ifndef BVH_H
#define BVH_H

#include "..\Objects\Triangle.h"
#include "..\Objects\Hitable.h"
#include <vector>

class BVH : public Hitable
{
public:
	BVH();
	BVH(std::vector<Hitable*> *_primsVector);
	~BVH();

	bool RayTraveral(std::vector<Hitable*> *primsVector,
			const Ray &ray, float tMin, float tMax, HitRecord &rec) const;

	bool Hit(const Ray &ray, float tMin, float tMax, HitRecord &rec) const override;
	bool BoundingBox(float t0, float t1, AABB &box) const override;

private:
	std::vector<Hitable*> *primsVector;
	// The bounding box surrounding all hitables
	AABB boundingBox;

};

#endif