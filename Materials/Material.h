#ifndef MATERIAL_H
#define MATERIAL_H

#include "..\Math\Ray.h"
#include "..\Hitable.h"

class Material
{
public:
	virtual bool Scatter(const Ray &rayIn, const HitRecord &hitRecord, Vector3 &attenuation, Ray &scattered) const = 0;
};

#endif