#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "Material.h"
#include "..\Math\Sampler.h"
#include "..\Objects\HitRecord.h"

class Lambertian : public Material
{
public:
	Lambertian(const Vector3 &a);

	virtual bool Scatter(const Ray &rayIn, const HitRecord &hitRecord, Vector3 &attenuation, Ray &scattered) const;

private:
	Vector3 albedo;
};

#endif