#include <iostream>
#include <assert.h>

#include "Scene\Scene.h"

int main()
{
	std::cout << "Dazzer_Raytracer\n" << std::endl;

	// NOTE(Darren): Might make a branch where i use external web tool profiler (maybe Remotery)
	Scene scene;
	scene.RenderScene();

	return 0;
}