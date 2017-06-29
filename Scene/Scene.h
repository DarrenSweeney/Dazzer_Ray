#ifndef SCENE_H
#define SCENE_H

#include <cfloat>
#include <thread>

// NOTE(Darren): Need to include because of incomplete class type with struct HitRecord
#include "..\Materials\Lambertian.h"
#include "..\Materials\Metal.h"
#include "..\Materials\Dielectric.h"
#include "..\Textures\ImageTexture.h"
#include "..\Textures\ConstantTexture.h"
#include "..\Objects\Sphere.h"
#include "..\Camera\Camera.h"
#include "..\IO\PPM_Image.h"
#include "..\Objects\HitableList.h"
#include <vector>

struct TileData
{
	unsigned int width;
	unsigned int height;
	unsigned int tileSize;
};

class Scene
{
public:
	Scene();
	~Scene();

	void RenderScene();

private:
	Vector3 Color(Ray &ray, HitableList *world, int depth);
	void RenderTile(unsigned int tilePosX, unsigned int tilePosY, 
		unsigned int tileWidth, unsigned int tileHeight);
	HitableList* TestScene();
	void AssignThreadsTiles();

	HitableList* sceneObects;
	std::vector<std::thread> threads;
	std::vector<TileData> tilesToRender;
	Camera camera;
	PPM_Image* ppmImage;
	uint8_t numOfThreads;
	unsigned int width, height, samples, tileSize;
};

#endif