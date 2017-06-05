#ifndef SCENE_H
#define SCENE_H

#include "Math\Ray.h"
// NOTE(Darren): Need to include because of incomplete class type with struct HitRecord
#include "Materials\Material.h"
#include <cfloat>

class Scene
{
public:
	Scene();

	Vector3 Color(Ray &ray, Hitable *world, int depth);
	void RenderScene();
};

#endif