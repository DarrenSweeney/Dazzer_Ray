#ifndef SCENE_H
#define SCENE_H

#include <cfloat>
#include <vector>
#include "Math\Ray.h"
// NOTE(Darren): Need to include because of incomplete class type with struct HitRecord
#include "Materials\Material.h"
#include "Objects\Sphere.h"
#include "Sampler.h"
#include "Camera\Camera.h"
#include "IO\PPM_Image.h"

class Scene
{
public:
	Scene();
	~Scene();

	void RenderScene();

private:
	Vector3 Color(Ray &ray, std::vector<Hitable*> &world, int depth);

	std::vector<Hitable*> TestScene();
	std::vector<Hitable*> sceneObects;
	Camera camera;
	PPM_Image ppmImage;
};

#endif