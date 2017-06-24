#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "Material.h"
#include "..\Math\Sampler.h"
#include "..\Objects\HitRecord.h"
#include "..\Textures\Texture.h"

class Lambertian : public Material
{
public:
	Lambertian(Texture *_albedo);
	~Lambertian();

	bool Scatter(const Ray &rayIn, const HitRecord &hitRecord, Vector3 &attenuation, Ray &scattered) const override;

private:
	Texture* albedo;
};

#endif