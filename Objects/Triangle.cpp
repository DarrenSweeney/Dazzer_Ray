#include "Triangle.h"

#define CULLING true

Triangle::Triangle() { }

Triangle::Triangle(Vector3 &_p1, Vector3 &_p2, Vector3 &_p3)
	: p1(_p1), p2(_p2), p3(_p3)
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
	// If the determinant is negative the triangle is backfacing
	// If the determinant is close to 0, the ray misses the triangle
	if (det < FLT_EPSILON)
		return false;
#else
	// Ray and triangle are parallel if det is close to 0
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

	return true;
}

// @refactor(Darren): Make this method beter, i think this has shown to much friction.
//					  Needs another look.
bool Triangle::BoundingBox(float t0, float t1, AABB &box) const
{
	Vector3 minExtent(fminf(fminf(p1.x, p2.x), p3.x), fminf(fminf(p1.y, p2.y), p3.y), fminf(fminf(p1.z, p2.z), p3.z));
	Vector3 maxExtent(fmaxf(fmaxf(p1.x, p2.x), p3.x), fmaxf(fmaxf(p1.y, p2.y), p3.y), fmaxf(fmaxf(p1.z, p2.z), p3.z));

	box = AABB(minExtent, maxExtent);

	return true;
}

Vector3 Triangle::Centroid() const
{
	// Todo(Darren): Implement the centroid function
	return Vector3();
}