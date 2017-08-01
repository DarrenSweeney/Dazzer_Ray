#ifndef MESH_H
#define MESH_H

#include "..\IO\OBJ_Parser.h"
#include "..\Objects\Triangle.h"

class Mesh : public Hitable
{
public:
	Mesh(tinyobj::attrib_t &attrib, std::vector<tinyobj::shape_t> &shapes, Material *_material);
	~Mesh();

	bool Hit(const Ray &ray, float tMin, float tMax, HitRecord &hitRecord) const override;
	bool BoundingBox(float t0, float t1, AABB &box) const override;

private:
	Material *material;
	std::vector<Triangle*> triangles;
	AABB boundingBox;
};

#endif