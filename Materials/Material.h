#ifndef MATERIAL_H
#define MATERIAL_H

#include "..\Math\Ray.h"
#include "..\Objects\HitRecord.h"

class Material
{
public:
	virtual bool Scatter(const Ray &rayIn, const HitRecord &hitRecord, Vector3 &attenuation, Ray &scattered) const = 0;
	virtual Vector3 Emitted(Vector2 uv, const Vector3 &p) const { return Vector3(); };
};

#endif