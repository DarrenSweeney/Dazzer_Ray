#define STB_IMAGE_IMPLEMENTATION

#include "Scene.h"

Scene::Scene()
	: width(800), height(400), samples(10)
{
	// TODO(Darren): May want to have each scene to contain camera data
	Vector3 cameraPosition(0.0f, 0.0f, 1.0f);
	Vector3 lookAtPos(0.0f, 0.0f, 0.0f);
	float distanceToFocus = 2.0f;
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

	// FLT_MAX is for x64, will not work on x86 as FLT_MAX is max possible value of float.
	if (world->Hit(ray, 0.001f, FLT_MAX, hitRecord))
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
	Hitable **list = new Hitable*[4];
	int i = 0;

	int width, height, comp;
	unsigned char *imageData = stbi_load("Resources/three.png", &width, &height, &comp, 0);
	Texture *ballTexture = new ImageTexture(imageData, width, height);

	// Ground
	list[i++] = new Sphere(Vector3(0.0f, -100.5f, -1.0f), 100.0f, 
		new Lambertian(new ConstantTexture(Vector3(0.8f, 0.3f, 0.3f))));

	list[i++] = new Sphere(Vector3(0.0f, 0.0f, -1.0f), 0.5f, new Lambertian(ballTexture));
	list[i++] = new Sphere(Vector3(1.0f, 0.0f, -1.0f), 0.5f, new Metal(Vector3(0.8f, 0.6f, 0.2f), 0.0f));
	list[i++] = new Sphere(Vector3(-1.0f, 0.0f, -1.0f), 0.5f, new Metal(Vector3(0.8f, 0.8f, 0.8f), 0.0f));

	return new HitableList(list, i);
}

void Scene::RenderScene()
{
	sceneObects = TestScene();

	for (unsigned int y = 0; y < height; y++)
	{
		for (unsigned int x = 0; x < width; x++)
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
			ppmImage->WritePixel(x, y, col);

			printf("Image Pos: (%d, %d)\n", x, y);
		}
	}

	printf("Saving...\n");
	ppmImage->SavePPM("TestScene", std::ofstream());
	printf("PPM Image Saved\n");
}