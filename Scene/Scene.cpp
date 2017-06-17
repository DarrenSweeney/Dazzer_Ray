#include "Scene.h"

Scene::Scene()
	: width(512), height(512), samples(10)
{
	// TODO(Darren): May want to have each scene to contain camera data
	Vector3 cameraPosition(0.0f, 5.0f, 15.0f);
	Vector3 lookAtPos(0.0f, 1.0f, 0.0f);
	float distanceToFocus = 10.0f;
	float aperture = 0.1f;
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

		return (1.0f - t) * Vector3(1.0f, 1.0f, 1.0f) + t * Vector3(0.5f, 0.7f, 1.0f);
	}
}

HitableList *Scene::TestScene()
{
	Hitable **list = new Hitable*[3];
	int i = 0;

	list[i++] = new Sphere(Vector3(0.0f, -100.5f, -1.0f), 100.0f, new Lambertian(Vector3(0.8f, 0.8f, 0.0f)));
	list[i++] = new Sphere(Vector3(0.0f, 0.0f, -1.0f), 0.5f, new Lambertian(Vector3(0.8f, 0.3f, 0.3f)));
	list[i++] = new Sphere(Vector3(1.0f, 0.0f, -1.0f), 0.5f, new Metal(Vector3(0.8f, 0.6f, 0.2f), 0.0f));
	list[i++] = new Sphere(Vector3(-1.0f, 0.0f, -1.0f), 0.5f, new Metal(Vector3(0.8f, 0.8f, 0.8f), 0.0f));

	return new HitableList(list, i);
}

HitableList *random_scene()
{
	int n = 100;
	Hitable **list = new Hitable*[n + 1];
	list[0] = new Sphere(Vector3(0, -1000, 0), 1000, new Lambertian(Vector3(0.5, 0.5, 0.5)));
	int i = 1;

	for (int a = -3; a < 3; a++)
	{
		for (int b = -3; b < 3; b++)
		{
			float choose_mat = randF(0.0f, 1.0f);
			Vector3 center(a + 0.9 * randF(0.0f, 1.0f), 0.2, b + 1.9 * randF(0.0f, 1.0f));
			if ((center - Vector3(4, 0.2, 0)).Lenght() > 0.9)
			{
				if (choose_mat < 0.8) // Diffuse
				{
					list[i++] = new Sphere(center, 0.2, new Lambertian(Vector3(randF(0.0f, 1.0f) * randF(0.0f, 1.0f),
						randF(0.0f, 1.0f) * randF(0.0f, 1.0f), randF(0.0f, 1.0f) * randF(0.0f, 1.0f))));
				}
				else if (choose_mat < 0.95) // Metal
				{
					list[i++] = new Sphere(center, 0.2,
						new Metal(Vector3(0.5 * (1 + randF(0.0f, 1.0f)), 0.5 * (1 + randF(0.0f, 1.0f)),
							0.5 * (1 + randF(0.0f, 1.0f))), 0.5 * randF(0.0f, 1.0f)));
				}
				else // Glass
				{
					list[i++] = new Sphere(center, 0.2, new Dielectric(1.5));
				}
			}
		}
	}

	list[i++] = new Sphere(Vector3(0, 1, 0), 1.0, new Dielectric(1.5));
	list[i++] = new Sphere(Vector3(-4, 1, 0), 1.0, new Lambertian(Vector3(0.4, 0.2, 0.1)));
	list[i++] = new Sphere(Vector3(4, 1, 0), 1.0, new Metal(Vector3(0.7, 0.6, 0.5), 0.0));

	return new HitableList(list, i);
}

void Scene::RenderScene()
{
	sceneObects = random_scene();

	for (unsigned int y = 0; y < width; y++)
	{
		for (unsigned int x = 0; x < height; x++)
		{
			Vector3 col;

			for (unsigned int s = 0; s < samples; s++)
			{
				float u = float(x + randF(0.0f, 1.0f)) / width;
				float v = float(y + randF(0.0f, 1.0f)) / height;

				Ray ray = camera.GetRay(u, v);
				Vector3 point = ray.PointAtParamater(2.0f);
				col += Color(ray, sceneObects, 0);
			}

			col /= float(samples);
			col = Vector3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			// TODO(Darren): Fix that it only works for square numbers for now
			ppmImage->WritePixel(x, y, col);

			printf("Image Pos: (%d, %d)\n", y, x);
		}
	}

	printf("Saving...\n");
	ppmImage->SavePPM("TestScene", std::ofstream());
	printf("PPM Image Saved\n");
}