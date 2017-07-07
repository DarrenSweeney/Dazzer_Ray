#include "Triangle.h"

#define CULLING false

Triangle::Triangle() { }

Triangle::Triangle(Vector3 &_p1, Vector3 &_p2, Vector3 &_p3, Material *_material)
	: p1(_p1), p2(_p2), p3(_p3), material(_material)
{

}

// Möller–Trumbore intersection algorithm
bool Triangle::Hit(const Ray &ray, float tMin, float tMax, HitRecord &hitRecord) const
{
	Vector3 d1 = p2 - p1;
	Vector3 d2 = p3 - p1;
	Vector3 pvec = Cross(ray.Direction(), d2);
	float det = Dot(d1, pvec);

#if CULLING
	// if the determinant is negative the triangle is backfacing
	// if the determinant is close to 0, the ray misses the triangle
	if (det < FLT_EPSILON)
		return false;
#else
	// ray and triangle are parallel if det is close to 0
	if (fabs(det) < FLT_EPSILON)
		return false;
#endif

	float invDet = 1 / det;

	Vector3 tvec = ray.Origin() - p1;
	float u = Dot(tvec, pvec) * invDet;

	if (u < 0 || u > 1) 
		return false;

	Vector3 qvec = Cross(tvec, d1);
	float v = Dot(ray.Direction(), qvec) * invDet;

	if (v < 0 || u + v > 1) 
		return false;

	float t = Dot(d2, qvec) * invDet;

	if (t < tMin)
		return false;

	hitRecord.t = t;
	hitRecord.point = ray.PointAtParamater(hitRecord.t);
	hitRecord.normal = Cross(d1, d2);
	hitRecord.material = material;

	return true;
}

// @Todo(Darren): Implement this
bool Triangle::BoundingBox(float t0, float t1, AABB &box) const
{
	return true;
}