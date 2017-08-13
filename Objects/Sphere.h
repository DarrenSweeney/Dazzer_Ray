#ifndef SPHERE_H
#define SPHERE_H

#include "..\Objects\Hitable.h"
#include "..\Math\MathUtil.h"
#include <float.h>

class Sphere : public Hitable
{
public:
	Sphere(const Vector3 &startPos, const Vector3 &endPos, float time0,  float time1, 
		const float &_radius, Material *material);
	Sphere(const Vector3 &position, const float &_radius, Material *material);
	~Sphere();

	bool Hit(const Ray &ray, float tMin, float tMax, HitRecord &hitRecord) const override;
	bool BoundingBox(float t0, float t1, AABB &box) const override;

private:
	Vector2 SphereUV(const Vector3 &p) const;
	Vector3 Center(float time) const;

	float radius;
	// For moition blur, static objects will have the same start/end pos and time
	Vector3 startPos, endPos;
	float time0, time1;
	bool motionBlur;
	Material *material;
};

#endif