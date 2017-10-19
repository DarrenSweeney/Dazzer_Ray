#include "Dielectric.h"

Dielectric::Dielectric(float ri)
	: refractiveIndex(ri) { }

bool Dielectric::Scatter(const Ray &rayIn, const HitRecord &hitRecord, Vector3 &attenuation, Ray &scattered) const
{
	Vector3 outwardNormal;
	Vector3 reflected = Reflect(rayIn.direction, hitRecord.normal);
	float ni_over_nt;
	attenuation = Vector3(1.0f, 1.0f, 1.0f);
	Vector3 refracted;
	float reflectProb;
	float cosine;
	
	if (Dot(rayIn.direction, hitRecord.normal) > 0)
	{
		outwardNormal = -hitRecord.normal;
		ni_over_nt = refractiveIndex;
		cosine = refractiveIndex * Dot(rayIn.direction, hitRecord.normal) / rayIn.direction.Length();
	}
	else
	{
		outwardNormal = hitRecord.normal;
		ni_over_nt = 1.0f / refractiveIndex;
		cosine = -Dot(rayIn.direction, hitRecord.normal) / rayIn.direction.Length();
	}

	if (Refract(rayIn.direction, outwardNormal, ni_over_nt, refracted))
	{
		reflectProb = Schlick(cosine, refractiveIndex);
	}
	else
	{
		scattered = Ray(hitRecord.point, reflected);
		reflectProb = 1.0f;
	}

	if (randF(0.0f, 1.0f) < reflectProb)
	{
		scattered = Ray(hitRecord.point, reflected);
	}
	else
	{
		scattered = Ray(hitRecord.point, refracted);
	}

	return true;
}

bool Dielectric::Refract(const Vector3 &v, const Vector3 &n, float ni_over_nt, Vector3 &refracted) const
{
	Vector3 uv = UnitVector(v);
	float dt = Dot(uv, n);
	float discriminant = 1.0f - (ni_over_nt * ni_over_nt) * (1 - dt * dt);

	if (discriminant > 0)
	{
		refracted = ni_over_nt * (uv - dt * n) - sqrt(discriminant) * n;
		return true;
	}
	else
		return false;
}

float Dielectric::Schlick(float cosine, float refractiveIndex) const
{
	float r0 = (1 - refractiveIndex) / (1 + refractiveIndex);
	r0 = r0 * r0;
	
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}