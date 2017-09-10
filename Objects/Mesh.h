#ifndef MESH_H
#define MESH_H

#include "..\IO\OBJ_Parser.h"
#include "..\Objects\Triangle.h"
#include "..\Accelerators\BVH.h"

class Mesh : public Hitable
{
public:
	Mesh(const char *fileLoc, Material *_material, uint8_t bvhLeafSize);
	~Mesh();

	bool Hit(const Ray &ray, float tMin, float tMax, HitRecord &hitRecord) const override;
	bool BoundingBox(float t0, float t1, AABB &box) const override;

private:
	Material *material;
	std::vector<Triangle*> triangles;
	AABB boundingBox;

	BVH *bvh;
};

#endif