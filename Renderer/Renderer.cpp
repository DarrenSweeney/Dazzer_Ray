#include "Renderer.h"

Renderer::Renderer(Scene *_scene, Camera *_camera, uint32_t _width,
	uint32_t _height, uint16_t _samples, uint8_t _numThreads)
	:	camera(_camera), scene(_scene), width(_width), height(_height), samples(_samples), numThreads(_numThreads)
{
	ppmImage = new PPM_Image(width, height);
}

Renderer::~Renderer()
{
	delete ppmImage;
}

Vector3 Renderer::Color(const Ray &ray, HitableList *world, uint16_t depth)
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


void Renderer::QueueThreadRenderTask()
{
	TileData tileToRender;

	{	
		std::lock_guard<std::mutex> lock(tileMutex);

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

	RenderTile(tileToRender);
}


void Renderer::RenderScene()
{
	{
		PROFILE("Total Render Time");

		// Divide the retangle image into chunks based of number of threads
		// @note(Darren): Gonna split across horizontal, so each tile can access data continous
		uint16_t tileWidth = width / numThreads;
		uint16_t sum = 0;
		for (uint16_t i = 0; i < numThreads; i++)
		{
			sum += tileWidth;
			uint16_t currentTilePos = tileWidth * i; // @note(Darren): Avoid narrowing converson here
			if (i == numThreads - 1 && sum != width)
			{
				// @todo(Darren): Fix this
				//tileWidth = width + (width - currentTileWidth);
			}
			tilesToRender.push_back(TileData{ currentTilePos, 0, tileWidth, height });
		}

		assert(sum == width);

		for (uint8_t i = 0; i < numThreads; i++)
		{
			threads.push_back(std::thread(&Renderer::QueueThreadRenderTask, this));
		}

		for (std::thread &t : threads)
		{
			if (t.joinable())
				t.join();
		}
	}

	printf("Saving...\n");
	ppmImage->SavePPM("TestScene", std::ofstream());
	printf("PPM Image Saved\n");
}

void Renderer::RenderTile(TileData &tileData)
{
	assert(tileData.tilePosX + tileData.tileWidth <= width);
	assert(tileData.tilePosY + tileData.tileHeight <= height);

	{
		// @todo(Darren): Add better profile names
		const char* profileName;
		PROFILE("Render_Image_Tile: ");

		for (uint16_t y = tileData.tilePosY; y < tileData.tilePosY + tileData.tileHeight; y++)
		{
			for (uint16_t x = tileData.tilePosX; x < tileData.tilePosX + tileData.tileWidth; x++)
			{
				Vector3 col;

				for (uint16_t s = 0; s < samples; s++)
				{
					float u = float(x + randF(0.0f, 1.0f)) / width;
					float v = float(y + randF(0.0f, 1.0f)) / height;

					Ray ray = camera->GetRay(u, v);
					Vector3 point = ray.PointAtParamater(2.0f);
					col += Color(ray, &scene->sceneObects, 0);
				}

				col /= float(samples);
				col = Vector3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
				ppmImage->WritePixel(x, y, col);
			}
		}
	}
}