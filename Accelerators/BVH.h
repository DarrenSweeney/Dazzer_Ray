#ifndef BVH_H
#define BVH_H

#include "..\Objects\Triangle.h"
#include "..\Objects\Hitable.h"
#include <vector>
#include <algorithm>
#include "..\Profiler.h"

class BVH_Node
{
public:
	BVH_Node();
	~BVH_Node();

	void MakeLeaf(uint32_t index, uint32_t nTriangles);

	BVH_Node* leftNode;
	BVH_Node* rightNode;
	uint32_t  startIndex;
	uint32_t nOfTriangles;
	AABB boundingBox;
	bool isLeaf;
};

class BVH : public Hitable
{
public:
	BVH(std::vector<Triangle*> *_primsVector, uint8_t leafSize = 1);
	~BVH();

	void Build();
	void BuildRecursive(uint32_t leftIndex, uint32_t rightIndex, BVH_Node *node);

	bool Hit(const Ray &ray, float tMin, float tMax, HitRecord &rec) const override;
	bool Hit(BVH_Node *node, const Ray &ray, float &tMin, float &tMax, HitRecord &rec) const;
	bool BoundingBox(float t0, float t1, AABB &box) const override;

private:
	// @note(Darren): Making this a Triangle, triangle is not a hitable right now.
	// Just leave until i get it working. Might have a BVH for scene of hitables 
	// and BVH for mesh of hitables
	// @note(Darren): When i make the bvh in the mesh class i will know the size already,
	//				  so maybe avoid dynamic memory of vector and allocate up front. 
	//				  Look into this.
	std::vector<Triangle*> *primsVector;
	uint8_t leafSize;

	BVH_Node *root;
};

#endif