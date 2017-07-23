#include "KD_Node.h"

KD_Node::KD_Node() { }

KD_Node::~KD_Node()
{
	for (Triangle *triangle : triangles)
		delete triangle;
}

KD_Node* KD_Node::Build(std::vector<Triangle*> &triangles, int depth) const
{
	KD_Node *kdNode = new KD_Node();
	kdNode->triangles = triangles;

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
	Vector3 midPoint;
	for (Triangle* triangle : triangles)
	{
		// Expand the triangle, ie get the surrounding bounding box
		AABB box;
		triangle->BoundingBox(0.0f, 0.0f, box);
		kdNode->boundingBox.ExpandBoundingBox(box);
		midPoint += box.max + box.min;
	}

	midPoint *= 0.5f * (1.0f / triangles.size());

	std::vector<Triangle*> leftTriangles, rightTriangles;
	Axis axis = kdNode->boundingBox.GetLongestAxis();
	for (Triangle* triangle : triangles)
	{
		AABB box;
		triangle->BoundingBox(0.0f, 0.0f, box);
		Vector3 currentTriangleMidPoint = (box.max + box.min) * 0.5f;
		switch (axis)
		{
		case Axis::X:
			midPoint.x <= currentTriangleMidPoint.x ? leftTriangles.push_back(triangle) : rightTriangles.push_back(triangle);
			break;
		case Axis::Y:
			midPoint.y <= currentTriangleMidPoint.y ? leftTriangles.push_back(triangle) : rightTriangles.push_back(triangle);
			break;
		case Axis::Z:
			midPoint.z <= currentTriangleMidPoint.z ? leftTriangles.push_back(triangle) : rightTriangles.push_back(triangle);
			break;
		}
	}

	// Count the total matches
	float matches = 0.0f;
	for (int i = 0; i < leftTriangles.size(); i++) 
	{
		for (int j = 0; j < rightTriangles.size(); j++) 
		{
			if (leftTriangles[i] == leftTriangles[j]) 
				matches++;
		}
	}

	// If 50% of the triangles match, don't subdivide any more
	if (matches / float(leftTriangles.size()) < 0.5f && matches / float(rightTriangles.size()) < 0.5f) 
	{
		// Recurse down left and right sides
		kdNode->left = Build(leftTriangles, depth + 1);
		kdNode->right = Build(rightTriangles, depth + 1);
	}
	else 
	{
		kdNode->left = new KD_Node();
		kdNode->right = new KD_Node();
	}

	return kdNode;
}

bool KD_Node::Hit(const Ray &ray, float tMin, float tMax, HitRecord &hitRecord)
{
	// Check if the ray intersects the current node bounding box
	if (boundingBox.Hit(ray, tMin, tMax))
	{
		// Check if either child node has triangles, if yes, recurse down tree for intersections
		if (left->triangles.size() > 0)
		{
			bool hitLeftNode = left->Hit(ray, tMin, tMax, hitRecord);
			return hitLeftNode;
		}
		else if (right->triangles.size() > 0)
		{
			bool hitRightNode = right->Hit(ray, tMin, tMax, hitRecord);
			return hitRightNode;
		}
		
		// If there are no child nodes, we have reached a leaf node
		else
		{
			float closestSoFar = tMax;

			// Check all triangles in the node for intersection
			for (Triangle *triangle : triangles)
			{
				if (triangle->Hit(ray, tMin, tMax, hitRecord))
				{
					closestSoFar = hitRecord.t;
					return true;
				}
			}
		}
	}

	return false;
}