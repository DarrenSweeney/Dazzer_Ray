#ifndef RENDERER_H
#define RENDERER_H

#include <thread>
#include <mutex>
#include <assert.h>

#include "..\Profiler.h"
#include "..\Camera\Camera.h"
#include "..\Scene\Scene.h"
#include "..\IO\PPM_Image.h"
#include "..\Materials\Material.h"

//class Scene;
//class HitableList;
//class Camera;

class Renderer
{
public:
	Renderer(uint32_t width, uint32_t height, uint16_t samples, uint8_t numThreads);
	~Renderer();

	void RenderScene(Camera *camera, Scene *scene);

private:
	struct TileData
	{
		uint16_t tilePosX;
		uint16_t tilePosY;
		uint16_t tileWidth;
		uint16_t tileHeight;
	};

	Vector3 Color(const Ray &ray, HitableList *world, uint16_t depth);
	void QueueThreadRenderTask(Camera *camera, Scene *scene);
	void RenderTile(Camera *camera, Scene *scene, const TileData &tileData);

	PPM_Image *ppmImage;
	uint16_t width, height;
	uint16_t samples;
	uint8_t numThreads;
	std::vector<TileData> tilesToRender;

	std::vector<std::thread> threads;
	std::mutex tileMutex;
};

#endif