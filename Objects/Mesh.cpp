#include "Mesh.h"

Mesh::Mesh(std::vector<Triangle*> &_triangles)
	: triangles(_triangles)
{
	kdNode = new KD_Node();
	kdNode = kdNode->Build(triangles, 0.0f);
}

Mesh::~Mesh()
{
	delete kdNode;
}

bool Mesh::Hit(const Ray &ray, float tMin, float tMax, HitRecord &hitRecord) const
{
	// @Todo(Darren): Need to fix the kd tree structure
	for (Triangle *triangle : triangles)
	//if (kdNode->Hit(ray, tMin, tMax, hitRecord))
	{
		// @Todo(Darren): may assing the material here for the hitrecord and take out 
		//					the triangle material and possibly hitable

		if (triangle->Hit(ray, tMin, tMax, hitRecord))
			return true;
	}

	return false;
}

bool Mesh::BoundingBox(float t0, float t1, AABB &box) const
{
	box = kdNode->boundingBox;

	return true;
}