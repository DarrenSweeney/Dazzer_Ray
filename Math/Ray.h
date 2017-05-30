#ifndef RAY_H
#define RAY_H

#include "Vector3.h"

/*
	p(t) = A + t * B

		where:	p - 3D pos along ray
				A - Ray Origin
				B - Ray Direction
				t - Ray parameter (any point on the line defined by the ray's origin and direction)
*/
class Ray
{
public:
	Ray() {}
	Ray(const Vector3 &_origin, const Vector3 &_direction, float ti = 0.0) : origin(_origin), direction(_direction), time(ti) {}
	
	Vector3 Origin() const { return origin; }
	Vector3 Direction() const { return direction; }
	Vector3 PointAtParamater(float t) const { return origin + t * direction; }
	float Time() const { return time; }

private:
	Vector3 origin, direction;
	float  time;
};

#endif