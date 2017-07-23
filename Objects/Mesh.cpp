#include "Mesh.h"

Mesh::Mesh(tinyobj::attrib_t &attrib, std::vector<tinyobj::shape_t> &shapes, Material *_material)
	: material(_material)
{
	std::vector<Vector3> vertexPositions;
	vertexPositions.reserve(attrib.vertices.size() / 3);
	for (int i = 0; i < attrib.vertices.size() / 3; i++)
	{
		vertexPositions.push_back(Vector3(attrib.vertices[i * 3 + 0], attrib.vertices[i * 3 + 1], attrib.vertices[i * 3 + 2]));
	}

	for (int i = 0; i < shapes.size(); i++)
	{
		for (int j = 0; j < shapes[i].mesh.indices.size() / 3; j++)
		{
			Vector3 p1 = vertexPositions[shapes[i].mesh.indices[j * 3 + 0].vertex_index];
			Vector3 p2 = vertexPositions[shapes[i].mesh.indices[j * 3 + 1].vertex_index];
			Vector3 p3 = vertexPositions[shapes[i].mesh.indices[j * 3 + 2].vertex_index];

			triangles.push_back(new Triangle(p1, p2, p3));
		}
	}
}

Mesh::~Mesh()
{
	for (int i = 0; i < triangles.size(); i++)
		delete triangles[i];
}

bool Mesh::Hit(const Ray &ray, float tMin, float tMax, HitRecord &hitRecord) const
{
	for (Triangle *triangle : triangles)
	{
		if (triangle->Hit(ray, tMin, tMax, hitRecord))
		{
			hitRecord.material = material;
			return true;
		}
	}

	return false;
}

bool Mesh::BoundingBox(float t0, float t1, AABB &box) const
{
	// @Todo(Darren): Implement bounding box, will look into BVH first

	return true;
}