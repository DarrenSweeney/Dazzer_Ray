#include "Sphere.h"

Sphere::Sphere(const Vector3 &_startPos, const float &_radius, Material *_material)
	: startPos(_startPos), radius(_radius), material(_material), endPos(_startPos), time0(0.0f), time1(0.0f), motionBlur(false)
{

}

Sphere::Sphere(const Vector3 &_startPos, const Vector3 &_endPos, float _time0, float _time1,
				const float &_radius, Material *_material)
	: startPos(_startPos), endPos(_endPos), time0(_time0), time1(_time1), radius(_radius), material(_material), motionBlur(true)
{

}

Sphere::~Sphere()
{
	if(material)
		delete material;
}

bool Sphere::Hit(const Ray &ray, float tMin, float tMax, HitRecord &hitRecord) const
{
	Vector3 center = Center(ray.Time());
	Vector3 m = ray.Origin() - center;
	// @note(Darren): The ray direction is not normalized
	// Dot product of a vector itself is the square lenght of that vector
	float a = Dot(ray.Direction(), ray.Direction());
	float b = Dot(m, ray.Direction());
	float c = Dot(m, m) - (radius * radius);
	float discriminant = b*b - a*c;

	if (discriminant > 0)
	{
		float temp = (-b - sqrtf(discriminant)) / a;

		if (temp < tMax && temp > tMin)
		{
			hitRecord.t = temp;
			hitRecord.point = ray.PointAtParamater(hitRecord.t);
			hitRecord.normal = (hitRecord.point - Center(ray.Time())) / radius;
			hitRecord.uv = SphereUV(hitRecord.normal);
			hitRecord.material = material;
			return true;
		}

		temp = (-b + sqrtf(discriminant)) / a;

		if (temp < tMax && temp > tMin)	
		{
			hitRecord.t = temp;
			hitRecord.point = ray.PointAtParamater(hitRecord.t);
			hitRecord.normal = (hitRecord.point - Center(ray.Time())) / radius;
			hitRecord.uv = SphereUV(hitRecord.normal);
			hitRecord.material = material;
			return true;
		}
	}

	return false;
}

Vector2 Sphere::SphereUV(const Vector3 &p) const
{
	float theta = asinf(p.y);
	float phi = atan2f(p.z, p.x);
	float u = 1 - (phi + PI) / (2 * PI);
	float v = (theta + PI / 2) / PI;

	return Vector2(u, v);
}

/*
	Time is from 0-1 as set up in scene
	Time between pos of sphere is also 0-1
*/
Vector3 Sphere::Center(float time) const
{
	if (!motionBlur)
		return startPos;
	else
		//				  |<--------Range from 0-1-------->|
		return startPos + ((time - time0) / (time1 - time0)) * (endPos - startPos);
}

bool Sphere::BoundingBox(float t0, float t1, AABB &box) const
{
	if (!motionBlur)
		box = AABB(startPos - Vector3(radius, radius, radius), startPos + Vector3(radius, radius, radius));
	else
	{
		AABB box0(Center(t0) - Vector3(radius, radius, radius), Center(t0) + Vector3(radius, radius, radius));
		AABB box1(Center(t1) - Vector3(radius, radius, radius), Center(t1) + Vector3(radius, radius, radius));
		box = box.GetSurroundingBox(box0, box1);
	}

	return true;
}