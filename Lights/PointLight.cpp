#include "PointLight.h"

PointLight::PointLight() { }

PointLight::PointLight(Vector3 &pos, Vector3 &_color, float _ls)
	: position(pos)
{
	color = _color;
	ls = _ls;
}

Vector3 PointLight::GetDirection(HitRecord &hitRecord) const 
{
	return UnitVector(position - hitRecord.point);
}

Vector3 PointLight::L(HitRecord& rec) 
{
	return ls * color;
}

bool PointLight::InShadow(const Ray &ray, const Hitable* hitable) const 
{
	float d = (position - ray.Origin()).Lenght();
	bool isInShadow = false;

	HitRecord rec;
	// @Todo(Darren): Remove this max value or pass in min and max
	if (hitable->Hit(ray, 0.001, 100000.0f, rec) && rec.t < d) 
		isInShadow  = true;

	// @Todo(Darren): Add Emmit function to material base class
	if (isInShadow)
	{
		Vector3 attenuation;
		Ray scattered;
		rec.material->Scatter(Ray(rec.point, ray.Direction()), rec, attenuation, scattered);
		float cosine = Dot(scattered.Direction(), ray.Direction());

		if (cosine > 0.001 && randF() < cosine) 
			return InShadow(scattered, hitable);
	}

	return isInShadow;
}