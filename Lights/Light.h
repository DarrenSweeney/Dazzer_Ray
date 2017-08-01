#ifndef LIGHT_H
#define LIGHT_H

#include "..\Math\Ray.h"
#include "..\Objects\Hitable.h"
#include "..\Materials\Material.h"

class Light
{
public:
	Light() : ls(1.0f), color(1.0f, 1.0f, 1.0f) { };
	virtual Vector3 GetDirection(HitRecord &hitRecord) const = 0;
	virtual Vector3 L(HitRecord &hitRecord) = 0;
	virtual bool InShadow(const Ray &ray, const Hitable *h) const = 0;

protected:
	float ls;
	Vector3 color;
};

#endif