#ifndef BVH_H
#define BVH_H

#include "..\Objects\Triangle.h"
#include "..\Objects\Hitable.h"
#include <vector>
#include <algorithm>

// Todo(Darren): Can i make this a very simple struct
class BVH_Node 
{
public:
	BVH_Node();
	~BVH_Node();

	void MakeLeaf(uint32_t index, uint32_t nTriangles);

	AABB boundingBox;
	BVH_Node* leftNode;
	BVH_Node* rightNode;
	// @note(Darren): Use unint32_t and the like more through out code?
	uint32_t  m_index;
	bool m_isLeaf;
	uint32_t m_nOfTriangles;
};

class BVH : public Hitable
{
public:
	BVH();
	BVH(std::vector<Triangle*> *_primsVector, int leafSize = 1);
	~BVH();

	void Build();
	void BuildRecursive(int leftIndex, int rightIndex, BVH_Node *node);

	bool Hit(const Ray &ray, float tMin, float tMax, HitRecord &rec) const override;
	bool BoundingBox(float t0, float t1, AABB &box) const override;

private:
	// Note(Darren): Making this a Triangle, triangle is not a hitable right now.
	// Just leave until i get it working. Might have a BVH for scene of hitables 
	// and BVH for mesh of hitables
	std::vector<Triangle*> *primsVector;
	std::vector<BVH_Node> nodeList;

	BVH_Node *root;
};

#endif