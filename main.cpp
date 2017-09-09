#include "DazzerRay.h"

int main()
{
	Material *material = new Metal(Vector3(1.0f, 1.0f, 1.0f), 0.65f);
	Material *redMat = new Lambertian(new ConstantTexture(Vector3(0.96f, 0.1f, 0.1f)));
	Material *greenMat = new Lambertian(new ConstantTexture(Vector3(0.1f, 0.96f, 0.1f)));
	Material *light1 = new DiffuseLight(new ConstantTexture(Vector3(0.65f, 0.5f, 0.15f)));
	Material *light2 = new DiffuseLight(new ConstantTexture(Vector3(0.85f, 0.12f, 0.35f)));
	Material *light3 = new DiffuseLight(new ConstantTexture(Vector3(1.0f, 1.0f, 1.0f)));

	// @note(Darren): Not working with metal material, triangle normal fliped makes it work out transparent
	Mesh *mesh = new Mesh("Resources/monkey.obj", new Lambertian(new ConstantTexture(Vector3(0.47f, 0.18f, 0.34f))));

	Scene scene;
	scene.Add(new Disk(Vector3(0.0f, -1.0f, 0.0f), UnitVector(Vector3(0.0f, 1.0f, 0.0f)), 4.0f, material));
	scene.Add(new XYRect(-2.5f, 2.5f, -1.0f, 2.0f, -1.0f, false, redMat));
	scene.Add(new YZRect(-1.0f, 2.0f, -2.0f, 2.0f, -2.5f, false, greenMat));
	scene.Add(new Sphere(Vector3(0.8f, -0.85f, 1.0f), 0.15f, light1));
	scene.Add(new Sphere(Vector3(-1.0f, -0.85f, 1.7f), 0.15f, light2));
	scene.Add(new Disk(Vector3(0.3f, 1.5f, 0.9f), UnitVector(Vector3(0.0f, 1.0f, 0.0f)), 0.75f, light3));
	scene.Add(mesh);

	Vector3 cameraPosition(1.0f, 0.0f, 4.0f);
	Vector3 lookAtPos(0.0f, 0.5f, 0.0f);
	float distanceToFocus = 10.0f;
	float aperture = 0.0f;
	float vfov = 90.0f;
	uint16_t width = 1024;
	uint16_t height = 512;

	Camera camera(cameraPosition, lookAtPos, Vector3(0.0f, 1.0f, 0.0f), vfov,
		float(width) / float(height), aperture, distanceToFocus, 0.0f, 1.0f);

	Renderer renderer(&scene, &camera, 1024, 512, 1, 4);
	renderer.RenderScene();

	return 0;
}