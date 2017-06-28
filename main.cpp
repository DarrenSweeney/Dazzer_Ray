
#include <iostream>
#include <assert.h>

#include "Scene\Scene.h"

int main()
{
	printf("Dazzer_Raytracer\n");

	// NOTE(Darren): Might make a branch where i use external web tool profiler (maybe Remotery)
	Scene scene;
	scene.RenderScene();

	return 0;
}