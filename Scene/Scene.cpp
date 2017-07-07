#define STB_IMAGE_IMPLEMENTATION
#define TINYOBJLOADER_IMPLEMENTATION
#define MULTITHREAD false

#include "Scene.h"

// @Darren: May want to take out the render functionality and put into RayTrace.cpp (or something)
//			Use scene to load in and save scenes to disk.
Scene::Scene()
	: width(1024), height(512), samples(10), tileSize(256), numOfThreads(2)
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

	//objParser.ParseObjFile("catmark_torus_creases0.obj");
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
	//list[i++] = new Sphere(Vector3(0.0f, -100.5f, -1.0f), 100.0f, 
		//new Lambertian(new ConstantTexture(Vector3(0.8f, 0.3f, 0.3f))));

	// Triangle
	list[i++] = new Triangle(Vector3(-0.5f, -0.5f, -1.0f), Vector3(0.0f, 0.2f, 0.0f), Vector3(0.5f, -0.5f, -4.0f),
		new Metal(Vector3(1.0f, 0.2f, 0.5f)));
	list[i++] = new Sphere(Vector3(0.25f, 0.5f, -1.0f), 0.1f, new Lambertian(ballTexture));
	list[i++] = new Sphere(Vector3(1.0f, 0.0f, -1.0f), 0.5f, new Metal(Vector3(0.8f, 0.6f, 0.2f), 0.0f));
	list[i++] = new Sphere(Vector3(-1.0f, 0.0f, -1.0f), 0.5f, new Metal(Vector3(0.8f, 0.8f, 0.8f), 0.0f));
	
	return new HitableList(list, i);
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
		@Darren: When the thread is finished rendering the scene how do i start again for remaining scenes?
	*/
	RenderTile(tileToRender);

	/*
		If another tile is avaible and this thread is done with RenderTIle(..) then
		call method again? Until all tiles are finished.
	*/
}

/*
	@Darren: Spereate the render scene into render image tile, then create two threads to render
	each tile as a test. Look into syncing and other threading stuff i need to learn.
*/
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
	RenderTile(tile);
#endif

	printf("Saving...\n");
	ppmImage->SavePPM("TestScene", std::ofstream());
	printf("PPM Image Saved\n");
}

void Scene::RenderTile(TileData &tileData)
{
	assert(tileData.tilePosX + tileData.tileWidth  <= width );
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