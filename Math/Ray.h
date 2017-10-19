#ifndef RAY_H
#define RAY_H

#include "Vector3.h"

/*
	p(t) = A + t * B

		where:	p - 3D pos along ray
				A - Ray Origin
				B - Ray Direction
				t - Ray parameter (any point on the line defined by the ray's origin and direction)

	@note(Darren): When B is normalized to unit length, t corresponds to the actual distance from start point A
*/
class Ray
{
public:
	Ray() { }
	Ray(const Vector3 &_origin, const Vector3 &_direction, float ti = 0.0)
		: origin(_origin), direction(_direction), time(ti) { }

	Vector3 PointAtParamater(float t) const { return origin + t * direction; }

	Vector3 origin, direction;
	float time;
};

#endif