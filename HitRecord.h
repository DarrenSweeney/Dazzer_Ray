#ifndef HIT_RECORD_H
#define HIT_RECORD_H

#include "Math\Vector3.h"
#include "Math\Vector2.h"

struct HitRecord
{
	float time;
	Vector3 point;
	Vector3 normal;
	Vector2 uv;
};

#endif
