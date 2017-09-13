#include "Plane.h"

Plane::Plane(Vector3 &_position, Vector3 &_normal, Material *_material)
	: position(_position), normal(UnitVector(_normal)), material(_material)
{

}

Plane::~Plane()
{
	if (material)
		delete material;
}

bool Plane::Hit(const Ray &ray, float tMin, float tMax, HitRecord &hitRecord) const
{
	float d = Dot(normal, ray.Direction());

	if (fabs(d) < 0.001f)
		return false;

	Vector3 a = position - ray.Origin();
	float t = Dot(a, normal) / d;
	if (t < 0.001f)
		return false;

	hitRecord.t = t;
	hitRecord.normal = normal;
	hitRecord.point = ray.PointAtParamater(t);
	hitRecord.material = material;

	return true;
}

bool Plane::BoundingBox(float t0, float t1, AABB &box) const
{
	box = AABB(Vector3(-INFINITY, -INFINITY, -INFINITY), Vector3(INFINITY, INFINITY, INFINITY));

	return true;
}