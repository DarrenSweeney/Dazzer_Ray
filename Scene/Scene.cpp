#include "Scene.h"

Scene::Scene()
	: width(255), height(255), samples(1)
{
	// TODO(Darren): May want to have each scene to contain camera data
	Vector3 cameraPosition(0.0f, 7.0f, -12.0f);
	Vector3 lookAtPos(0.0f, 1.0f, 0.0f);
	float distanceToFocus = 10.0f;
	float aperture = 0.0f;
	float vfov = 40.0f;
	camera = Camera(cameraPosition, lookAtPos, Vector3(0.0f, 1.0f, 0.0f), vfov,
		float(width) / float(height), aperture, distanceToFocus, 0.0f, 1.0f);

	ppmImage = new PPM_Image(width, height);
}

Scene::~Scene()
{
	delete ppmImage;
}

Vector3 Scene::Color(Ray &ray, HitableList *world, int depth)
{
	HitRecord hitRecord;

	if (world->Hit(ray, hitRecord))
	{
		Ray scattered;
		Vector3 attenuation;

		// NOTE(Darren): Would it be possible to add string id to objects 
		//				 to make it easier to debug them. (only in debug mode)
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

HitableList *Scene::TestScene()
{
	Hitable **list = new Hitable*[3];
	int i = 0;
	// Ground
	list[i++] = new Sphere(Vector3(0.0f, -100.0f, 0.0f), 100.0f, new Lambertian(Vector3(0.5f, 0.1f, 0.9f)));

	list[i++] = new Sphere(Vector3(0.0f, 1.0f, 0.0f), 1.0f, new Lambertian(Vector3(1.0f, 0.0f, 0.0f)));
	list[i++] = new Sphere(Vector3(-2.0f, 1.0f, 0.0f), 1.0f, new Lambertian(Vector3(0.0f, 1.0f, 0.0f)));
	list[i++] = new Sphere(Vector3(2.0f, 1.0f, 0.0f), 1.0f, new Lambertian(Vector3(0.0f, 0.0f, 1.0f)));

	return new HitableList(list, i);
}

void Scene::RenderScene()
{
	sceneObects = TestScene();

	for (unsigned int y = 0; y < width; y++)
	{
		for (unsigned int x = 0; x < height; x++)
		{
			Vector3 col;

			for (unsigned int s = 0; s < samples; s++)
			{
				float u = float(x + randF(0.0f, 1.0f)) / 255.0f;
				float v = float(y + randF(0.0f, 1.0f)) / 255.0f;

				Ray ray = camera.GetRay(u, v);
				Vector3 point = ray.PointAtParamater(2.0f);
				col += Color(ray, sceneObects, 0);
			}

			col /= float(samples);
			col = Vector3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			ppmImage->WritePixel(x, y, col);

			printf("Image Pos: (%d, %d)\n", y, x);
		}
	}

	printf("Saving...\n");
	ppmImage->SavePPM("TestScene", std::ofstream());
	printf("PPM Image Saved\n");
}