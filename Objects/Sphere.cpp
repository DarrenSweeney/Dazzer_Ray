#include "Sphere.h"

Sphere::Sphere()
	: radius(0.0f)
{

}

Sphere::Sphere(const Vector3 &_center, const float &_radius)
	: center(_center), radius(_radius)
{

}

bool Sphere::Hit(const Ray &ray, HitRecord &hitRecord) const
{
	Vector3 m = ray.Origin() - center;
	float b = Dot(m, ray.Direction());
	float c = Dot(m, m) - (radius * radius);

	/*
		Return false if ray's origin is outside sphere, c > 0.0f
		and the ray is pointing away from the sphere, b > 0.0f	
	*/
	if (c > 0.0f && b > 0.0f)
		return false;

	float discriminant = b*b - c;
	// If the discriminant is less than zero, ray missed sphere
	if (discriminant < 0.0f)
		return false;

	float t = -b - sqrtf(discriminant);

	// If t is negative, ray started inside sphere so clamp t to zero
	if (t < 0.0f)
		t = 0.0f;

	hitRecord.t = t;
	hitRecord.point = ray.PointAtParamater(t);
	hitRecord.normal = (hitRecord.point - center) / radius;

	return true;
}

bool Sphere::BoundingBox(float t0, float t1, AABB &box) const
{
	box = AABB(center - Vector3(radius, radius, radius), center + Vector3(radius, radius, radius));

	return true;
}