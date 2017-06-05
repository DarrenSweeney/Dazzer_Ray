#include "Scene.h"

Scene::Scene()
{

}

Vector3 Scene::Color(Ray &ray, Hitable *world, int depth)
{
	HitRecord hitRecord;

	if (world->Hit(ray, 0.001f, FLT_MAX, hitRecord))
	{
		Ray scattered;
		Vector3 attenuation;

		if (depth < 50 && hitRecord.material->Scatter(ray, hitRecord, attenuation, scattered))
		{
			return attenuation * Color(scattered, world, depth + 1);
		}
		else
			return Vector3();
	}
	else
	{

		Vector3 unitDirection = UnitVector(ray.Direction());
		float t = 0.5f * (unitDirection.y + 1.0f);

		return (1.0f - t) * Vector3(1.0f, 1.0f, 1.0f) + t * Vector3(0.9f, 0.7f, 1.0f);
	}
}

void Scene::RenderScene()
{
	// TODO(Darren): Implement render of scene, may use basic hitableList for now instead 
	//				 of creating a BVH. Too sleepy, time for Mass Effect : Andromeda <3 \:D/
}