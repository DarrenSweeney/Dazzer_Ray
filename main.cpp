#include <iostream>

// NOTE(Darren): Might make a branch where i use external web tool profiler (maybe Remotery)

#include "Scene\Scene.h"

int main()
{
	std::cout << "Dazzer_Raytracer\n" << std::endl;

	Scene scene;
	scene.RenderScene();

	return 0;
}