#include "Mesh.h"

Mesh::Mesh(const char *fileLoc, Material *_material, uint8_t leafSize)
	: material(_material)
{
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	ParseObjFile(attrib, shapes, materials, fileLoc);

	std::vector<Vector3> vertexPositions;
	vertexPositions.reserve(attrib.vertices.size() / 3);
	for (size_t i = 0; i < attrib.vertices.size() / 3; i++)
	{
		vertexPositions.push_back(Vector3(attrib.vertices[i * 3 + 0], attrib.vertices[i * 3 + 1], attrib.vertices[i * 3 + 2]));
	}

	for (size_t i = 0; i < shapes.size(); i++)
	{
		for (size_t j = 0; j < shapes[i].mesh.indices.size() / 3; j++)
		{
			Vector3 p1 = vertexPositions[shapes[i].mesh.indices[j * 3 + 0].vertex_index];
			Vector3 p2 = vertexPositions[shapes[i].mesh.indices[j * 3 + 1].vertex_index];
			Vector3 p3 = vertexPositions[shapes[i].mesh.indices[j * 3 + 2].vertex_index];

			triangles.push_back(new Triangle(p1, p2, p3));
		}
	}

	// Create the bounding volume hierarchy for the mesh
	bvh = new BVH(&triangles, leafSize);

	AABB box;
	for (size_t i = 1; i < triangles.size(); i++)
	{
		triangles[i]->BoundingBox(0.0f, 0.0f, box);
		boundingBox = boundingBox.ExpandBoundingBox(box);
	}
}

Mesh::~Mesh()
{
	for (Triangle *triangle : triangles)
		delete triangle;

	if (material)
		delete material;

	delete bvh;
}

bool Mesh::Hit(const Ray &ray, float tMin, float tMax, HitRecord &hitRecord) const
{
	if (bvh->Hit(ray, tMin, tMax, hitRecord))
	{
		hitRecord.material = material;
		return true;
	}

	return false;
}

bool Mesh::BoundingBox(float t0, float t1, AABB &box) const
{
	box = boundingBox;

	return true;
}