#ifndef RECT_H
#define RECT_H

#include "..\Materials\Material.h"
#include "Hitable.h"

class XYRect : public Hitable
{
public:
	XYRect();
	XYRect(float _x0, float _x1, float _y0, float _y1, float _k, bool _flipNormal, Material *material);
	~XYRect();

	bool Hit(const Ray &ray, float t_min, float t_max, HitRecord &rec) const override;
	bool BoundingBox(float t0, float t1, AABB &box) const override;

private:
	Material *material;
	bool flipNormal;
	float x0, x1, y0, y1, k;
};

class XZRect : public Hitable
{
public:
	XZRect();
	XZRect(float _x0, float _x1, float _z0, float _z1, float _k, bool flipNormal, Material *material);
	~XZRect();

	bool Hit(const Ray &ray, float t_min, float t_max, HitRecord &rec) const override;
	bool BoundingBox(float t0, float t1, AABB &box) const override;

private:
	Material *material;
	bool flipNormal;
	float x0, x1, z0, z1, k;
};

class YZRect : public Hitable
{
public:
	YZRect();
	YZRect(float _y0, float _y1, float _z0, float _z1, float _k, bool flipNormal, Material *material);
	~YZRect();

	bool Hit(const Ray &ray, float t_min, float t_max, HitRecord &rec) const override;
	bool BoundingBox(float t0, float t1, AABB &box) const override;

private:
	Material *material;
	bool flipNormal;
	float y0, y1, z0, z1, k;
};

#endif