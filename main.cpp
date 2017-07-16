#include "Scene\Scene.h"

// @Todo(Darren): Put stb image into IO?

int main()
{
	printf("Dazzer_Raytracer\n");

	// NOTE(Darren): Might make a branch where i use external web tool profiler (maybe Remotery)
	Scene scene;
	scene.RenderScene();

	return 0;
}