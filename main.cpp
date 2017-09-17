#include "DazzerRay.h"

int main()
{
	Vector3 cameraPosition(0.0f, 2.2f, 3.0f);
	Vector3 lookAtPos(0.0f, 0.25f, 0.0f);
	float distanceToFocus = 10.0f;
	float aperture = 0.0f;
	float vfov = 90.0f;
	uint16_t width = 1024;
	uint16_t height = 512;

	Camera camera(cameraPosition, lookAtPos, Vector3(0.0f, 1.0f, 0.0f), vfov,
		float(width) / float(height), aperture, distanceToFocus, 0.0f, 1.0f);

	Material *redMat = new Lambertian(new ConstantTexture(Vector3(0.96f, 0.1f, 0.1f)));
	Material *greenMat = new Lambertian(new ConstantTexture(Vector3(0.1f, 0.96f, 0.1f)));

	Scene scene;
	scene.Add(new Plane(Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), redMat));
	scene.Add(new Sphere(Vector3(0.0f, 1.0f, 0.5f), 1.0f, greenMat));

	Renderer renderer(&scene, &camera, width, height, 1, 4);
	renderer.RenderScene();

	return 0;
}