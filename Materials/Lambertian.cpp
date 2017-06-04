#include "Lambertian.h"

Lambertian::Lambertian(const Vector3 &a)
	: albedo(a) { }

bool Lambertian::Scatter(const Ray &rayIn, const HitRecord &hitRecord, Vector3 &attenuation, Ray &scattered) const
{
	Vector3 target = hitRecord.point + hitRecord.normal + RandomInUnitSphere();
	scattered = Ray(hitRecord.point, target - hitRecord.point);
	attenuation = albedo;
	return true;
}