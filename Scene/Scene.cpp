#define STB_IMAGE_IMPLEMENTATION
#define TINYOBJLOADER_IMPLEMENTATION
#define MULTITHREAD true

#include "Scene.h"

Scene::Scene()
	: width(1024), height(512), samples(1), tileSize(256), numOfThreads(4)
{
	Vector3 cameraPosition(1.0f, 0.0f, 4.0f);
	Vector3 lookAtPos(0.0f, 0.5f, 0.0f);
	float distanceToFocus = 10.0f;
	float aperture = 0.0f;
	float vfov = 90.0f;

	camera = Camera(cameraPosition, lookAtPos, Vector3(0.0f, 1.0f, 0.0f), vfov,
		float(width) / float(height), aperture, distanceToFocus, 0.0f, 1.0f);

	ppmImage = new PPM_Image(width, height);

	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	ParseObjFile(attrib, shapes, materials, "Resources/monkey.obj");
	// @todo(Darren): Implement error handling for mesh loading
	// @note(Darren): Not working with metal material, triangle normal fliped makes it work out transparent
	mesh = new Mesh(attrib, shapes, new Lambertian(new ConstantTexture(Vector3(0.47f, 0.18f, 0.34f))));
}

Scene::~Scene()
{
	delete ppmImage;
	delete mesh;
}

Vector3 Scene::Color(Ray &ray, Hitable *world, int depth)
{
	HitRecord hitRecord;

	// @Note(Darren): FLT_MAX is for x64, will not work on x86 as FLT_MAX is max possible value of float.
	if (world->Hit(ray, 0.001f, FLT_MAX, hitRecord))
	{
		Ray scattered;
		Vector3 attenuation;
		Vector3 emmited = hitRecord.material->Emitted(hitRecord.uv, hitRecord.point);
		
		if (depth < 50 && hitRecord.material->Scatter(ray, hitRecord, attenuation, scattered))
			return emmited + attenuation * Color(scattered, world, depth + 1);
		else
			return emmited;
	}
	else
	{
		Vector3 unitDirection = UnitVector(ray.Direction());
		float t = 0.5f * (unitDirection.y + 1.0f);

		return Lerp(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.23f, 0.37f, 0.41f), t);
	}
}

HitableList *Scene::TestScene()
{
	Hitable **list = new Hitable*[7];
	int i = 0;

	Material *material = new Metal(Vector3(1.0f, 1.0f, 1.0f), 0.65f);
	Material *redMat = new Lambertian(new ConstantTexture(Vector3(0.96f, 0.1f, 0.1f)));
	Material *greenMat = new Lambertian(new ConstantTexture(Vector3(0.1f, 0.96f, 0.1f)));
	Material *light1 = new DiffuseLight(new ConstantTexture(Vector3(0.65f, 0.5f, 0.15f)));
	Material *light2 = new DiffuseLight(new ConstantTexture(Vector3(0.85f, 0.12f, 0.35f)));
	Material *light3 = new DiffuseLight(new ConstantTexture(Vector3(1.0f, 1.0f, 1.0f)));

	list[i++] = new Disk(Vector3(0.0f, -1.0f, 0.0f), UnitVector(Vector3(0.0f, 1.0f, 0.0f)), 4.0f, material);
	list[i++] = new XYRect(-2.5f, 2.5f, -1.0f, 2.0f, -1.0f, false, redMat);
	list[i++] = new YZRect(-1.0f, 2.0f, -2.0f, 2.0f, -2.5f, false, greenMat);
	list[i++] = mesh;
	list[i++] = new Sphere(Vector3(0.8f, -0.85f, 1.0f), 0.15f, light1);
	list[i++] = new Sphere(Vector3(-1.0f, -0.85f, 1.7f), 0.15f, light2);
	list[i++] = new Disk(Vector3(0.3f, 1.5f, 0.9f), UnitVector(Vector3(0.0f, 1.0f, 0.0f)), 0.75f, light3);

	return new HitableList(list, i);
}

void Scene::QueueThreadRenderTask()
{
	TileData tileToRender;

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

	{
		// @todo(Darren): Add more info

		PROFILE("Render_Image_Tile: ");
		RenderTile(tileToRender);
	}
}

void Scene::RenderScene()
{
	sceneObects = TestScene();

#if MULTITHREAD
	// Dived the retangle image into chunks based of number of threads
	// @note(Darren): Gonna split across horizontal, so each tile can access data continous
	uint8_t splitNum = numOfThreads;
	uint16_t tileWidth = width / splitNum;
	uint16_t sum = 0;
	for (uint16_t i = 0; i < splitNum; i++)
	{
		sum += tileWidth;		
		uint16_t currentTileWidth = tileWidth * i; // @note(Darren): Avoid narrowing converson here
		if (i == splitNum  - 1 && sum != width)
			currentTileWidth = width - currentTileWidth;
		tilesToRender.push_back(TileData{ currentTileWidth, 0, tileWidth, height });
	}

	assert(sum == width);

	for (uint8_t i = 0; i < numOfThreads; i++)
	{
		threads.push_back(std::thread(&Scene::QueueThreadRenderTask, this));
	}

	for (std::thread &t : threads)
	{
		if (t.joinable()) 
			t.join();
	}
#else
	TileData tile{0, 0, width, height};

	{
		PROFILE("Render_Image");
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

	for (uint16_t y = tileData.tilePosY; y < tileData.tilePosY + tileData.tileHeight; y++)
	{
		for (uint16_t x = tileData.tilePosX; x < tileData.tilePosX + tileData.tileWidth; x++)
		{
			Vector3 col;

			for (uint16_t s = 0; s < samples; s++)
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
		}
	}
}