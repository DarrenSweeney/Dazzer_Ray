#ifndef MESH_H
#define MESH_H

#include "..\Accelerators\KD_Node.h"

class Mesh : public Hitable
{
public:
	Mesh(std::vector<Triangle*> &triangles);
	~Mesh();

	bool Hit(const Ray &ray, float tMin, float tMax, HitRecord &hitRecord) const override;
	bool BoundingBox(float t0, float t1, AABB &box) const override;

private:
	KD_Node *kdNode;
	std::vector<Triangle*> triangles;

	// @Todo(Darren): Check the address of this against the kdNode triangles
};

#endif