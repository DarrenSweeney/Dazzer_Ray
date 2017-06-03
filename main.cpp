#include <iostream>

// NOTE(Darren): Might make a branch where i use external web tool profiler

#include "HitRecord.h"
#include "IO\PPM_Image.h"

int main()
{
	std::cout << "Dazzer_Raytracer\n" << std::endl;

	PPM_Image ppm(2, 2);
	ppm.WritePixel(0, 0, Vector3(0.1f, 0.5f, 0.2f));
	ppm.WritePixel(0, 1, Vector3(0.1f, 1.5f, 0.23f));
	ppm.WritePixel(1, 0, Vector3(0.1f, 3.5f, 0.27f));
	ppm.WritePixel(1, 1, Vector3(0.1f, 4.5f, 0.7f));
	ppm.SavePPM("RayTracing_Scene");

	return 0;
}