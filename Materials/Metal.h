#ifndef METAL_H
#define METAL_H

#include "Material.h"
#include "..\Math\Sampler.h"

class Metal : public Material
{
public:
	Metal(const Vector3 &_albedo, const float roughness);

	bool Scatter(const Ray &rayIn, const HitRecord &hitRecord, Vector3 &attenuation, Ray &scattered) const override;

private:
	Vector3 albedo;
	float roughness;
};

#endif