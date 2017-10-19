#include "Metal.h"

Metal::Metal(const Vector3 &_albedo, const float _roughness)
	: albedo(_albedo), roughness(_roughness)
{
	
}

bool Metal::Scatter(const Ray &rayIn, const HitRecord &hitRecord, Vector3 &attenuation, Ray &scattered) const
{
	Vector3 reflected = Reflect(UnitVector(rayIn.direction), hitRecord.normal);
	scattered = Ray(hitRecord.point, reflected + roughness * RandomInUnitSphere());
	attenuation = albedo;

	return (Dot(scattered.direction, hitRecord.normal) > 0);
}