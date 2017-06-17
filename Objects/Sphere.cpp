#include "Sphere.h"

Sphere::Sphere()
	: radius(0.0f)
{

}

Sphere::Sphere(const Vector3 &_center, const float &_radius, Material *_material)
	: center(_center), radius(_radius), material(_material)
{

}

Sphere::~Sphere()
{
	if(material)
		delete material;
}

bool Sphere::Hit(const Ray &ray, HitRecord &hitRecord) const
{
	Vector3 m = ray.Origin() - center;
	float a = Dot(ray.Direction(), ray.Direction());
	float b = Dot(m, ray.Direction());
	float c = Dot(m, m) - (radius * radius);
	float discriminant = b*b - a*c;

	if (discriminant > 0)
	{
		float temp = (-b - sqrt(discriminant)) / a;

		if (temp < FLT_MAX && temp > 0.001f)
		{
			hitRecord.t = temp;
			hitRecord.point = ray.PointAtParamater(hitRecord.t);
			hitRecord.normal = (hitRecord.point - center) / radius;
			hitRecord.material = material;
			return true;
		}

		temp = (-b + sqrt(discriminant)) / a;

		if (temp < FLT_MAX && temp > 0.001f)
		{
			hitRecord.t = temp;
			hitRecord.point = ray.PointAtParamater(hitRecord.t);
			hitRecord.normal = (hitRecord.point - center) / radius;
			hitRecord.material = material;
			return true;
		}
	}

	return false;
}

bool Sphere::BoundingBox(float t0, float t1, AABB &box) const
{
	box = AABB(center - Vector3(radius, radius, radius), center + Vector3(radius, radius, radius));

	return true;
}