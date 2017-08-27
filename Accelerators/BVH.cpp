#include "BVH.h"

BVH_Node::BVH_Node()
	: m_index(0), m_isLeaf(false), m_nOfTriangles(0), leftNode(nullptr), rightNode(nullptr)
{

}

BVH_Node::~BVH_Node()
{
	if (!m_isLeaf)
	{
		if (leftNode) 
			delete leftNode;
		if (rightNode) 
			delete rightNode;
	}
}

void BVH_Node::MakeLeaf(uint32_t index, uint32_t nTriangles)
{
	m_isLeaf = true;
	m_index = index;
	m_nOfTriangles = nTriangles;
}

BVH::BVH(std::vector<Triangle*> *_primsVector, int _leafSize)
	: primsVector(_primsVector), leafSize(_leafSize)
{
	Build();
}

BVH::~BVH()
{
	for (Triangle *hitable : *primsVector)
		delete hitable;

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

void BVH::BuildRecursive(int leftIndex, int rightIndex, BVH_Node *node)
{
	// Check if the number of hitables is less than the threshold
	if ((rightIndex - leftIndex) <= leafSize)
	{
		node->MakeLeaf(leftIndex, rightIndex - leftIndex);
	}
	// @Todo(Darren): Is is bad that i am branching most of the time, because most of the time
	// the number of hitables will be less than the threshold?
	else
	{
		// Find the longest axis of the current node bounding box and use it as the splitting axis
		AABB nodeBound = node->boundingBox;
		Axis axis = nodeBound.GetLongestAxis();
		// @refactor(Darren): I don't like this code
		Vector3 axisVec_debug = (nodeBound.min + nodeBound.max);
		float midPointOnAxis = axisVec_debug[static_cast<uint8_t>(axis)] * 0.5f;

		// Sort the hitables in this dimension
		switch (axis)
		{
		case Axis::X:
			std::sort(primsVector->begin() + leftIndex, primsVector->begin() + rightIndex,
				[](const Triangle *t1, const Triangle *t2) -> bool { return t1->Centroid().x < t2->Centroid().x; });
			break;
		case Axis::Y:
			std::sort(primsVector->begin() + leftIndex, primsVector->begin() + rightIndex,
				[](const Triangle *t1, const Triangle *t2) -> bool { return t1->Centroid().y < t2->Centroid().y; });
			break;
		case Axis::Z:
			std::sort(primsVector->begin() + leftIndex, primsVector->begin() + rightIndex,
				[](const Triangle *t1, const Triangle *t2) -> bool { return t1->Centroid().z < t2->Centroid().z; });
			break;
		}

		// Find the splt index where the mid point divides the primitives in a left and right side
		// @todo(Darren): Try binary search
		int splitIndex = leftIndex;
		for (size_t i = leftIndex; i < rightIndex; i++)
		{
			// @todo(Darren): Get Axis to use ints as default, maybe just get bvh working for now
			if (primsVector->at(i)->Centroid()[static_cast<uint8_t>(axis)] > midPointOnAxis)
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
	return false;
}

bool BVH::BoundingBox(float t0, float t1, AABB &box) const
{
	box = root->boundingBox;

	return true;
}