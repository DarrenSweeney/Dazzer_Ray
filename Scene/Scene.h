#ifndef SCENE_H
#define SCENE_H

#include <cfloat>
#include <thread>
#include <mutex>
#include <vector>

#include "..\Materials\Lambertian.h"
#include "..\Materials\Metal.h"
#include "..\Materials\Dielectric.h"
#include "..\Lights\DiffuseLight.h"

#include "..\Textures\ImageTexture.h"
#include "..\Textures\ConstantTexture.h"

#include "..\Objects\HitableList.h"
#include "..\Objects\Sphere.h"
#include "..\Objects\Mesh.h"
#include "..\Objects\Plane.h"
#include "..\Objects\Disk.h"
#include "..\Objects\Rect.h"

#include "..\Camera\Camera.h"

#include "..\IO\PPM_Image.h"
#include "..\IO\OBJ_Parser.h"
#include "..\IO\stb_image.h"

#include "..\Accelerators\BVH.h"
#include "..\Profiler.h"

struct TileData
{
	uint16_t tilePosX;
	uint16_t tilePosY;
	uint16_t tileWidth;
	uint16_t tileHeight;
};

class Scene
{
public:
	Scene();
	~Scene();

	void RenderScene();

private:
	Vector3 Color(Ray &ray, Hitable *world, int depth);
	void RenderTile(TileData &date);
	HitableList* TestScene();
	void QueueThreadRenderTask();

	Hitable *sceneObects;
	std::vector<std::thread> threads;
	std::mutex tileMutex;
	std::vector<TileData> tilesToRender;
	Camera camera;
	PPM_Image *ppmImage;
	Mesh *mesh;
	uint8_t numOfThreads;
	uint16_t width, height, samples, tileSize;
};

#endif