#include "BVH.h"

BVH_Node::BVH_Node()
	: startIndex(0), isLeaf(false), nOfTriangles(0), leftNode(nullptr), rightNode(nullptr)
{

}

BVH_Node::~BVH_Node()
{
	if (!isLeaf)
	{
		if (leftNode) 
			delete leftNode;
		if (rightNode) 
			delete rightNode;
	}
}

void BVH_Node::MakeLeaf(uint32_t index, uint32_t nTriangles)
{
	isLeaf = true;
	startIndex = index;
	nOfTriangles = nTriangles;
}

BVH::BVH(std::vector<Triangle*> *_primsVector, uint8_t _leafSize)
	: primsVector(_primsVector), leafSize(_leafSize)
{
	PROFILE("BVH::Build");
	Build();
}

BVH::~BVH()
{
	delete root;
}

void BVH::Build()
{
	// Calculate the world bounding box for the root node
	AABB worldBound;
	primsVector->at(0)->BoundingBox(0.0f, 0.0f, worldBound);
	for(size_t i = 1; i < primsVector->size(); i++)
	{
		AABB hitableBound;
		primsVector->at(i)->BoundingBox(0.0f, 0.0f, hitableBound);
		worldBound = worldBound.ExpandBoundingBox(hitableBound);
	}

	int leftIndex = 0;
	int rightIndex = primsVector->size();

	// Set the world bounding box to the root node
	root = new BVH_Node();
	root->boundingBox = worldBound;

	BuildRecursive(leftIndex, rightIndex, root);
}

void BVH::BuildRecursive(uint32_t leftIndex, uint32_t rightIndex, BVH_Node *node)
{
	// @todo(Darren): Take this out
	static int counter = 0;
	counter++;
	printf("Counter is at: %i\n", counter);

	// Check if the number of hitables is less than the threshold
	if ((rightIndex - leftIndex) <= leafSize)
	{
		node->MakeLeaf(leftIndex, rightIndex - leftIndex);
	}
	else
	{
		// Find the longest axis of the current node bounding box and use it as the splitting axis
		AABB nodeBound = node->boundingBox;
		uint8_t longestAxis = nodeBound.GetLongestAxis();
		Vector3 nodeAxis = (nodeBound.min + nodeBound.max);
		
		float midPointOnAxis = nodeAxis[longestAxis] * 0.5f;

		// Sort the hitables in this dimension
		switch (longestAxis)
		{
		case 0:
			std::sort(primsVector->begin() + leftIndex, primsVector->begin() + rightIndex,
				[](const Triangle *t1, const Triangle *t2) -> bool { return t1->Centroid().x < t2->Centroid().x; });
			break;
		case 1:
			std::sort(primsVector->begin() + leftIndex, primsVector->begin() + rightIndex,
				[](const Triangle *t1, const Triangle *t2) -> bool { return t1->Centroid().y < t2->Centroid().y; });
			break;
		case 2:
			std::sort(primsVector->begin() + leftIndex, primsVector->begin() + rightIndex,
				[](const Triangle *t1, const Triangle *t2) -> bool { return t1->Centroid().z < t2->Centroid().z; });
			break;
		}

		// Find the splt index where the mid point divides the primitives in a left and right side
		uint8_t splitIndex = leftIndex;
		for (size_t i = leftIndex; i < rightIndex; i++)
		{
			if (primsVector->at(i)->Centroid()[longestAxis] > midPointOnAxis)
			{
				splitIndex = i;
				break;
			}
		}

		// Allocate two new nodes
		BVH_Node *leftNode = new BVH_Node();
		BVH_Node *rightNode = new BVH_Node();

		// Find the bounding box for the left and right node
		AABB leftBound;
		primsVector->at(leftIndex)->BoundingBox(0.0f, 0.0f, leftBound);
		for (size_t i = leftIndex + 1; i < splitIndex; i++)
		{
			AABB primsBound;
			primsVector->at(i)->BoundingBox(0.0f, 0.0f, primsBound);
			leftBound = leftBound.ExpandBoundingBox(primsBound);
		}

		AABB rightBound;
		primsVector->at(splitIndex)->BoundingBox(0.0f, 0.0f, rightBound);
		for (size_t i = splitIndex + 1; i < rightIndex; i++)
		{
			AABB primsBound;
			primsVector->at(i)->BoundingBox(0.0f, 0.0f, primsBound);
			rightBound = rightBound.ExpandBoundingBox(primsBound);
		}

		leftNode->boundingBox = leftBound;
		rightNode->boundingBox = rightBound;

		// Set the parent node it's left and right child node
		node->leftNode = leftNode;
		node->rightNode = rightNode;

		BuildRecursive(leftIndex, splitIndex, leftNode);
		BuildRecursive(splitIndex, rightIndex, rightNode);
	}
}

bool BVH::Hit(const Ray &ray, float tMin, float tMax, HitRecord &rec) const
{
	if (!root) return false;

	float closestSoFar = tMax;
	if (root->boundingBox.Hit(ray, tMin, closestSoFar))
	{
		bool hit = Hit(root, ray, tMin, closestSoFar, rec);
		return hit;
	}

	return false;
}

bool BVH::Hit(BVH_Node *node, const Ray &ray, float &tMin, float &tMax, HitRecord &rec) const
{
	bool isIntersection = false;

	// We are not at a leaf node so check the left and right node of the current node
	if (!node->isLeaf)
	{
		float tL0 = 0.0001f;
		float tL1 = FLT_MAX;

		float tR0 = 0.0001f;
		float tR1 = FLT_MAX;

		BVH_Node *firstNode = 0;
		BVH_Node *secondNode = 0;
		BVH_Node *leftNode = node->leftNode;

		if (leftNode)
		{
			bool intersectedL = leftNode->boundingBox.Hit(ray, tL0, tL1);
			if (intersectedL && tL0 <= tMax)
			{
				firstNode = leftNode;
			}
		}

		BVH_Node *rightNode = node->rightNode;
		if (rightNode)
		{
			bool intersectedR = rightNode->boundingBox.Hit(ray, tR0, tR1);
			if (intersectedR && tR0 <= tMax)
			{
				secondNode = rightNode;
			}
		}

		if (firstNode)
		{
			float thit1 = tMax;
			bool isIntersect1 = Hit(firstNode, ray, tMin, thit1, rec);

			if (isIntersect1 && thit1 < tMax)
			{
				tMax = thit1;
				isIntersection = true;
			}
		}

		if (secondNode)
		{
			float thit2 = tMax;

			bool isIntersect2 = Hit(secondNode, ray, tMin, thit2, rec);

			if (isIntersect2 && thit2 < tMax)
			{
				tMax = thit2;
				isIntersection = true;
			}
		}

	}
	// Check intersection for all triangles contained in the leaf node
	else
	{
		uint32_t startIndex = node->startIndex;
		uint32_t noOfTriangles = node->nOfTriangles;

		for (uint32_t i = startIndex; i < startIndex + noOfTriangles; i++)
		{
			if (primsVector->at(i)->Hit(ray, tMin, tMax, rec))
			{
				isIntersection = true;
				// Record the closest hit
				tMax = rec.t;
			}
		}
	}

	return isIntersection;
}

bool BVH::BoundingBox(float t0, float t1, AABB &box) const
{
	box = root->boundingBox;

	return true;
}