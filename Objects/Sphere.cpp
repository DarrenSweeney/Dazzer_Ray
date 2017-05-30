#include "Sphere.h"

Sphere::Sphere()
	: radius(0.0f)
{

}

Sphere::Sphere(const Vector3 &_center, const float &_radius)
	: center(_center), radius(_radius)
{

}

bool Sphere::Hit(const Ray &ray, float tMin, float tMax, HitRecord &hitRecord) const
{
	// TODO(Darren): Implementation

	return false;
}

bool Sphere::BoundingBox(float t0, float t1, AABB &box) const
{
	box = AABB(center - Vector3(radius, radius, radius), center + Vector3(radius, radius, radius));

	return true;
}