#include "Rect.h"

XYRect::XYRect() { }

XYRect::XYRect(float _x0, float _x1, float _y0, float _y1, float _k, bool _flipNormal, Material *mat)
	: x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), flipNormal(_flipNormal), material(mat)
{

}

XYRect::~XYRect()
{
	if (material)
		delete material;
}

bool XYRect::Hit(const Ray &ray, float t_min, float t_max, HitRecord &hitRecord) const
{
	float t = (k - ray.Origin().z) / ray.Direction().z;

	if (t < t_min || t > t_max)
		return false;

	Vector3 point = ray.PointAtParamater(t);

	if (point.x < x0 || point.x > x1 || point.y < y0 || point.y > y1)
		return false;

	hitRecord.uv = Vector2((point.x - x0) / (x1 - x0), (point.y - y0) / (y1 - y0));
	hitRecord.t = t;
	hitRecord.material = material;
	hitRecord.point = point;
	hitRecord.normal = flipNormal ? Vector3(0.0f, 0.0f, -1.0f) : Vector3(0.0f, 0.0f, 1.0f);

	return true;
}

bool XYRect::BoundingBox(float t0, float t1, AABB &box) const
{
	box = AABB(Vector3(x0, y0, k - 0.0001f), Vector3(x1, y1, k + 0.0001f));

	return true;
}

XZRect::XZRect() { }

XZRect::XZRect(float _x0, float _x1, float _z0, float _z1, float _k, bool _flipNormal, Material *mat)
	: x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k), flipNormal(_flipNormal), material(mat)
{

}

XZRect::~XZRect()
{
	if (material)
		delete material;
}

bool XZRect::Hit(const Ray &ray, float t_min, float t_max, HitRecord &hitRecord) const
{
	float t = (k - ray.Origin().y) / ray.Direction().y;

	if (t < t_min || t > t_max)
		return false;

	Vector3 point = ray.PointAtParamater(t);

	if (point.x < x0 || point.x > x1 || point.z < z0 || point.z > z1)
		return false;

	hitRecord.uv = Vector2((point.x - x0) / (x1 - x0), (point.z - z0) / (z1 - z0));
	hitRecord.t = t;
	hitRecord.material = material;
	hitRecord.point = point;
	hitRecord.normal = flipNormal ? Vector3(0.0f, 1.0f, 0.0f) : Vector3(0.0f, -1.0f, 0.0f);

	return true;
}

bool XZRect::BoundingBox(float t0, float t1, AABB &box) const
{
	box = AABB(Vector3(x0, k - 0.0001f, z0), Vector3(x1, k + 0.0001f, z1));

	return true;
}

YZRect::YZRect() { }

YZRect::YZRect(float _y0, float _y1, float _z0, float _z1, float _k, bool _flipNormal, Material *mat)
	: y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k), flipNormal(_flipNormal), material(mat)
{

}

YZRect::~YZRect()
{
	if (material)
		delete material;
}

bool YZRect::Hit(const Ray &ray, float t_min, float t_max, HitRecord &hitRecord) const
{
	float t = (k - ray.Origin().x) / ray.Direction().x;

	if (t < t_min || t > t_max)
		return false;

	Vector3 point = ray.PointAtParamater(t);

	if (point.y < y0 || point.y > y1 || point.z < z0 || point.z > z1)
		return false;

	hitRecord.uv = Vector2((point.y - y0) / (y1 - y0), (point.z - z0) / (z1 - z0));
	hitRecord.t = t;
	hitRecord.material = material;
	hitRecord.point = point;
	hitRecord.normal = flipNormal ? Vector3(-1.0f, 0.0f, 0.0f) : Vector3(1.0f, 0.0f, 0.0f);

	return true;
}

bool YZRect::BoundingBox(float t0, float t1, AABB &box) const
{
	box = AABB(Vector3(k - 0.0001f, y0, z0), Vector3(k + 0.0001f, y1, z1));

	return true;
}