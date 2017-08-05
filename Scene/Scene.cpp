#define STB_IMAGE_IMPLEMENTATION
#define TINYOBJLOADER_IMPLEMENTATION
#define MULTITHREAD false

#include "Scene.h"

// @Note(Darren): May want to take out the render functionality and put into RayTrace.cpp (or something)
//			Use scene to load in and save scenes to disk. Create a renderer which takes a reference
//			to a scene. Scene had scene.Add(...) function.

Scene::Scene()
	: width(1024), height(512), samples(10), tileSize(256), numOfThreads(2)
{
	Vector3 cameraPosition(0.0f, 3.0f, 6.0f);
	Vector3 lookAtPos(0.0f, 0.0f, 0.0f);
	float distanceToFocus = 10.0f;
	float aperture = 0.0f;
	float vfov = 40.0f;

	camera = Camera(cameraPosition, lookAtPos, Vector3(0.0f, 1.0f, 0.0f), vfov,
		float(width) / float(height), aperture, distanceToFocus, 0.0f, 1.0f);

	ppmImage = new PPM_Image(width, height);

	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	ParseObjFile(attrib, shapes, materials, "Resources/monkey.obj");
	mesh = new Mesh(attrib, shapes, new Lambertian(new ConstantTexture(Vector3(1.0f, 0.2f, 0.5f))));
}

Scene::~Scene()
{
	delete ppmImage;
	delete mesh;

	for (Light *light : lights)
	{
		delete light;
	}
}

Vector3 Scene::Color(Ray &ray, Hitable *world, int depth)
{
	HitRecord hitRecord;

	// @Note(Darren): FLT_MAX is for x64, will not work on x86 as FLT_MAX is max possible value of float.
	if (world->Hit(ray, 0.001f, FLT_MAX, hitRecord))
	{
		Ray scattered;
		Vector3 attenuation;
		
		if (depth < 50 && hitRecord.material->Scatter(ray, hitRecord, attenuation, scattered))
		{
			for (const Light *light : lights)
			{
				Vector3 wi = light->GetDirection(hitRecord);
				float dot = Dot(hitRecord.normal, wi);

				if (dot < 0.001f)
					continue;

				Ray shadowRay(hitRecord.point, wi);
				bool isInShadow = light->InShadow(ray, 0.001f, FLT_MAX, world);

				if (!isInShadow)
					attenuation += attenuation * light->L() * dot;
			}

			return attenuation * Color(scattered, world, depth + 1);
		}
		else
			return Vector3();
	}
	else
	{
		Vector3 unitDirection = UnitVector(ray.Direction());
		float t = 0.5f * (unitDirection.y + 1.0f);

		return (1.0f - t) * Vector3(0.0f, 0.0f, 0.0f) + t * Vector3(0.23f, 0.37f, 0.41f);
	}
}

HitableList *Scene::TestScene()
{
	Hitable **list = new Hitable*[5];
	int i = 0;

	int width, height, comp;
	unsigned char *imageData = stbi_load("Resources/three.png", &width, &height, &comp, 0);
	Texture *ballTexture = new ImageTexture(imageData, width, height);

	// Ground
	list[i++] = new Sphere(Vector3(0.0f, -100.5f, 0.0f), 100.0f, new Lambertian(new ConstantTexture(Vector3(0.6f, 1.0f, 1.0f))));

	list[i++] = new Sphere(Vector3(0.0f, 1.5f, -0.2f), 0.45f, new Lambertian(ballTexture));
	list[i++] = new Sphere(Vector3(1.0f, 0.0f, 1.2f), 0.5f, new Metal(Vector3(0.8f, 0.6f, 0.2f), 0.0f));
	list[i++] = new Sphere(Vector3(-1.0f, 0.0f, 1.2f), 0.5f, new Metal(Vector3(0.8f, 0.8f, 0.8f), 0.0f));
	list[i++] = new Sphere(Vector3(0.0f, 0.65f, 2.0f), 0.65f, new Lambertian(new ConstantTexture(Vector3(0.6f, 0.8f, 0.5f)))); //mesh;

	lights.clear();
	lights.push_back(new PointLight(Vector3(1.0f, 2.0f, 1.2f), Vector3(1.0f, 0.0f, 0.0f), 0.8f));
	
	return new HitableList(list, i);
}

Hitable* BVH_TestScene()
{
	std::vector<Hitable*> hitables;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			hitables.push_back(new Sphere(Vector3(-1.0f + j, 0.5f, -1.0f + i), 0.1f, new Lambertian(new ConstantTexture(Vector3(1.0f, 0.0f, 0.0f)))));
		}
	}

	return new BVH(&hitables);
}


/*
	@TODO(Darren): Give each available thread a tile to render, threads that are finished are 
					assigned a new tile to render.

					I want to test one thread doing all tiles vs no multithreading. Time to change
					rendering of a different tile.

				->	Look into pool of threads. Queues and dequeues.
*/
void Scene::QueueThreadRenderTask()
{
	TileData tileToRender;

	// @Note(Darren): Testing out a beter way with mutex's still have a lot of questions
	{ std::lock_guard<std::mutex> lock(tileMutex);

		if (tilesToRender.size() <= 0)
			return;

		// Get a tile that needs to be rendered
		tileToRender = {
			tilesToRender.back()
		};

		std::cout << "Current Tile being rendered: " << tilesToRender.size()
			<< " Rendered by Thread: " << std::this_thread::get_id() << std::endl;

		// Remove the tile as it's going to be rendered
		tilesToRender.pop_back();
	}

	/*
		@Note(Darren): When the thread is finished rendering the scene how do i start again for remaining scenes?
	*/
	RenderTile(tileToRender);

	/*
		If another tile is avaible and this thread is done with RenderTIle(..) then
		call method again? Until all tiles are finished.
	*/
}

void Scene::RenderScene()
{
	sceneObects = TestScene();

#if MULTITHREAD
	// Divide the scene image into tiles based on the tileSize
	for (unsigned int y = 0; y < height; y += tileSize)
	{
		unsigned int yTile = tileSize < height - y ? tileSize : height - y;

		for (unsigned int x = 0; x < width; x += tileSize)
		{
			unsigned int xTile = tileSize < width - x ? tileSize : width - x;

			tilesToRender.push_back({x, y, xTile, yTile});
		}
	}

	/*
		Loop through all tiles to render and test how slower or faster it is.
	*/
	/*for (int i = 0; i < tilesToRender.size(); i++)
	{
		RenderTile(tilesToRender.at(i));

		std::cout << "Current Tile being rendered: " << i << std::endl;
	}*/

	for (uint8_t i = 0; i < numOfThreads; i++)
	{
		/*
			@NOTE(Darren): Need to think to about to go onto next avaible tile.
		*/
		threads.push_back(std::thread(&Scene::QueueThreadRenderTask, this));
	}

	for (std::thread &t : threads)
	{
		if (t.joinable()) 
			t.join();
	}
#else
	TileData tile = {0, 0, width, height};

	{
		PROFILE("RenderTile");
		RenderTile(tile);
	}

#endif

	printf("Saving...\n");
	ppmImage->SavePPM("TestScene", std::ofstream());
	printf("PPM Image Saved\n");
}

void Scene::RenderTile(TileData &tileData)
{
	assert(tileData.tilePosX + tileData.tileWidth  <= width);
	assert(tileData.tilePosY + tileData.tileHeight <= height);

	for (unsigned int y = tileData.tilePosY; y < tileData.tilePosY + tileData.tileHeight; y++)
	{
		for (unsigned int x = tileData.tilePosX; x < tileData.tilePosX + tileData.tileWidth; x++)
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

			//printf("Image Pos: (%d, %d)\n", x, y);
		}
	}
}