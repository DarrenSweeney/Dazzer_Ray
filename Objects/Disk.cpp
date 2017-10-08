#include "Disk.h"

Disk::Disk(Vector3 &_position, Vector3 &_normal, float _radius, Material *_material)
	: position(_position), normal(UnitVector(_normal)), radius(_radius), material(_material)
{

}

Disk::~Disk()
{
	if (material)
		delete material;
}

bool Disk::Hit(const Ray &ray, float tMin, float tMax, HitRecord &hitRecord) const
{
	float d = Dot(normal, ray.Direction());

	if (fabs(d) < 0.001f)
		return false;

	Vector3 a = position - ray.Origin();
	float t = Dot(a, normal) / d;
	if (t < 0.001f)
		return false;

	Vector3 point = ray.PointAtParamater(t);
	float distanceToPlaneOrigin = (position - point).Length();

	if (distanceToPlaneOrigin >= radius)
		return false;

	hitRecord.t = t;
	hitRecord.normal = normal;
	hitRecord.point = point;
	hitRecord.material = material;

	return true;
}

bool Disk::BoundingBox(float t0, float t1, AABB &box) const
{
	box = AABB(position - Vector3(radius, radius, radius), position + Vector3(radius, radius, radius));

	return true;
}