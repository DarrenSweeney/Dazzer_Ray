#include "KD_Node.h"

KD_Node::KD_Node() { }

KD_Node* KD_Node::Build(std::vector<Triangle*> &triangles, int depth) const
{
	KD_Node *kdNode = new KD_Node();

	if (triangles.size() == 0)
	{
		kdNode->boundingBox = AABB();
		kdNode->left = nullptr;
		kdNode->right = nullptr;

		return kdNode;
	}

	if (triangles.size() == 1)
	{
		triangles[0]->BoundingBox(0.0f, 0.0f, kdNode->boundingBox);
		kdNode->left = new KD_Node();
		kdNode->right = new KD_Node();
		return kdNode;
	}

	// Get the bounding box that is surrounding all the triangles
	triangles[0]->BoundingBox(0.0f, 0.0f, kdNode->boundingBox);
	for (int i = 0; i < triangles.size(); i++)
	{
		// Expand the triangle, ie get the surrounding bounding box
		AABB box;
		triangles[i]->BoundingBox(0.0f, 0.0f, box);
		kdNode->boundingBox.ExpandBoundingBox(box);
	}

	// @Todo(Darren): Get the midpoint of the kd tree next
}

bool KD_Node::Hit(const Ray *ray, float tMin, float tMax, HitRecord &hitRecord)
{
	return true;
}