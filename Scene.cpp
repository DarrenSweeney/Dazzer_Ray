#include "Scene.h"

Scene::Scene() { }

Scene::~Scene()
{
	// TODO(Darren): Delete heap allocated vector of hitable objects,
	//					or use unique pointer.
}

// TODO(Darren): Haven't decided to leave in depth parameter yet
Vector3 Scene::Color(Ray &ray, std::vector<Hitable*> &world, int depth)
{
	HitRecord hitRecord;

	for (Hitable* object : world)
	{
		if (object->Hit(ray, hitRecord))
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
}

std::vector<Hitable*> TestScene()
{
	std::vector<Hitable*> sceneObjects;

	sceneObjects.push_back(new Sphere(Vector3(0.0f, 1.0f, 0.0f), 1.0f));

	return sceneObjects;
}

void Scene::RenderScene()
{
	for (unsigned int y = 255; y > 0; y--)
	{
		for (unsigned int x = 0; x < 255; x++)
		{
			Vector3 col;

			for (int s = 0; s < 10; s++)
			{
				float u = float(x + randF(0.0f, 1.0f)) / 255.0f;
				float v = float(y + randF(0.0f, 1.0f)) / 255.0f;

				Ray ray = camera.GetRay(u, v);
				Vector3 point = ray.PointAtParamater(2.0f);
				col += Color(ray, sceneObects, 0);
			}

			col /= float(10);
			col = Vector3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			ppmImage.WritePixel(x, y, col);

			printf("Image Pos: (%d, %d)\n", y, x);
		}
	}

	ppmImage.SavePPM("TestScene");
}