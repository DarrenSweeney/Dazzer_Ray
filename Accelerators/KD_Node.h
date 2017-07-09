#ifndef KD_NODE_H
#define KD_NODE_H

#include <vector>

#include "..\Math\AABB.h"
#include "..\Objects\Triangle.h"

class KD_Node
{
public:
	KD_Node();
	KD_Node* Build(std::vector<Triangle*> &triangles, int depth) const;
	bool Hit(const Ray *ray, float tMin, float tMax, HitRecord &hitRecord);

private:
	AABB boundingBox;
	KD_Node *left, *right;
	std::vector<Triangle*> triangles;
};

#endif