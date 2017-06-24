#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "Material.h"
#include "..\Math\Sampler.h"

class Dielectric : public Material
{
public:
	Dielectric(float ri);

	bool Scatter(const Ray &rayIn, const HitRecord &hitRecord, Vector3 &attenuation, Ray &scattered) const override;

private:
	bool Refract(const Vector3 &v, const Vector3 &n, float ni_over_nt, Vector3 &refracted) const;
	float Schlick(float cosine, float refractiveIndex) const;

	float refractiveIndex;
};

#endif