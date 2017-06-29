#define STB_IMAGE_IMPLEMENTATION
#define MULTITHREAD true

#include "Scene.h"

// @Darren: May want to take out the render functionality and put into RayTrace.cpp (or something)
//			Use scene to load in and save scenes to disk.
Scene::Scene()
	: width(800), height(400), samples(10), tileSize(256), numOfThreads(2)
{
	// @TODO(Darren): May want to have each scene to contain camera data
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

	// @Darren: FLT_MAX is for x64, will not work on x86 as FLT_MAX is max possible value of float.
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

/*
	@TODO(Darren): Give each avaible thread a tile to render, threads that are finished are 
					assigned a new tile to render.
*/
void Scene::AssignThreadsTiles()
{
	
}

/*
	@Darren: Spereate the render scene into render image tile, then create two threads to render
	each tile as a test. Look into syncing and other threading stuff i need to learn.
*/
void Scene::RenderScene()
{
	sceneObects = TestScene();

	// Divide the scene image into tiles based on the tileSize
	for (unsigned int y = 0; y < height; y++)
	{
		unsigned int yTile = tileSize < height - tileSize ? tileSize : height - tileSize;

		for (unsigned int x = 0; x < width; x++)
		{
			unsigned int xTile = tileSize < width - tileSize ? tileSize : width - tileSize;

			tilesToRender.push_back({xTile, yTile, tileSize});
		}
	}

#if MULTITHREAD
	/*
		Need to create a vector/array of threads based on how many tiles there are.
		Go across the x axis loop, increment based on tileSize, width is fmin(tileSize, (width - tilePosX)
	*/
	std::thread thread_1(&Scene::RenderTile, this, 0, 0, width / 2, height);						// Top Bottom
	std::thread thread_2(&Scene::RenderTile, this, 0, height / 2, width / 2,  height / 2);			// Top Left
	std::thread thread_3(&Scene::RenderTile, this, width / 2, 0, width / 2, height / 2);			// Bottom Right
	std::thread thread_4(&Scene::RenderTile, this, width / 2, height / 2, width / 2, height / 2);	// Top Right

	if (thread_1.joinable()) thread_1.join();
	if (thread_2.joinable()) thread_2.join();
	if (thread_3.joinable()) thread_3.join();
	if (thread_4.joinable()) thread_4.join();
#else
	RenderTile(0, 0, width, height);
#endif

	printf("Saving...\n");
	ppmImage->SavePPM("TestScene", std::ofstream());
	printf("PPM Image Saved\n");
}

void Scene::RenderTile(unsigned int tilePosX, unsigned int tilePosY,
	unsigned int tileWidth, unsigned int tileHeight)
{
	assert(tilePosX + tileWidth  <= width );
	assert(tilePosY + tileHeight <= height);

	for (unsigned int y = tilePosY; y < tilePosY + tileHeight; y++)
	{
		for (unsigned int x = tilePosX; x < tilePosX + tileWidth; x++)
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
}