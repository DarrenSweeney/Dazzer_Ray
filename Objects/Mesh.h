#ifndef MESH_H
#define MESH_H

#include "..\Accelerators\KD_Node.h"
#include "..\IO\OBJ_Parser.h"

class Mesh : public Hitable
{
public:
	Mesh(tinyobj::attrib_t &attrib, std::vector<tinyobj::shape_t> &shapes, Material *_material);
	~Mesh();

	bool Hit(const Ray &ray, float tMin, float tMax, HitRecord &hitRecord) const override;
	bool BoundingBox(float t0, float t1, AABB &box) const override;

private:
	KD_Node *kdNode;
	Material *material;
	std::vector<Triangle*> triangles;
};

#endif