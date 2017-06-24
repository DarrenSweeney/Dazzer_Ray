#ifndef HIT_RECORD_H
#define HIT_RECORD_H

#include "..\Math\Vector3.h"
#include "..\Math\Vector2.h"

class Material;

// TODO(Darren): Test layout in memory with timing.
struct HitRecord
{
	Vector3 point;
	Vector3 normal;
	Vector2 uv;
	float t;
	Material *material;
};

#endif