#include "DazzerRay.h"

int main()
{
	Material *redMat = new Lambertian(new ConstantTexture(Vector3(0.96f, 0.1f, 0.1f)));
	Material *greenMat = new Lambertian(new ConstantTexture(Vector3(0.1f, 0.96f, 0.1f)));
	Material *blueMat = new Lambertian(new ConstantTexture(Vector3(0.1f, 0.1f, 0.96f)));
	Material *whiteMat = new Lambertian(new ConstantTexture(Vector3(0.73f, 0.73f, 0.73f)));
	Material *blackMat = new Lambertian(new ConstantTexture(Vector3()));
	Material *light3 = new DiffuseLight(new ConstantTexture(Vector3(1.0f, 1.0f, 1.0f)));

	Mesh *cubeMesh = new Mesh("Resources/cube.obj", new Metal(Vector3(0.47f, 0.98f, 0.59f), 0.85f), 6);
	Mesh *teapotMesh = new Mesh("Resources/utah_teapot.obj", new Lambertian(new ConstantTexture(Vector3(0.5f, 0.6f, 0.2f))), 60);

	Vector3 cameraPosition(0.0f, 3.0f, 3.9f);
	Vector3 lookAtPos(0.0f, 3.0f, 0.0f);
	float distanceToFocus = 10.0f;
	float aperture = 0.0f;
	float vfov = 75.0f;
	uint16_t width = 1024;
	uint16_t height = 1024;

	Camera camera(cameraPosition, lookAtPos, Vector3(0.0f, 1.0f, 0.0f), vfov,
		float(width) / float(height), aperture, distanceToFocus, 0.0f, 1.0f);

	Scene scene;
	scene.Add(new XZRect(-4.0f, 4.0f, -4.0f, 3.0f,  0.0f, true, whiteMat));
	scene.Add(new XZRect(-4.0f, 4.0f, -3.0f, 3.0f,  6.0f, false, whiteMat));
	scene.Add(new XYRect(-4.0f, 4.0f, 0.0f, 6.0f, -4.0f, false, whiteMat));
	scene.Add(new XYRect(-4.0f, 4.0f, 0.0f, 6.0f, 4.0f, false, blackMat));
	scene.Add(new YZRect(0.0f, 7.0f, -4.0f, 4.0f, -3.5f, false, redMat));
	scene.Add(new YZRect(0.0f, 7.0f, -4.0f, 4.0f,  3.5f, true, greenMat));
	scene.Add(cubeMesh);
	scene.Add(teapotMesh);
	scene.Add(new XZRect(-3.0f, 3.0f, -3.5f, -3.0f, 0.0f, true, light3));
	scene.Add(new XZRect(-3.0f, 3.0f, 3.5f, 3.0f, 0.0f, true, light3));
	scene.Add(new XZRect(-3.0f, -2.5f, -3.5f, 3.0f, 0.0f, true, light3));
	scene.Add(new XZRect(2.5f, 3.0f, -3.5f, 3.0f, 0.0f, true, light3));

	Renderer renderer(&scene, &camera, width, height, 512, 4);
	renderer.RenderScene();

	return 0;
}

/* Cornell Box
	
	Material *redMat = new Lambertian(new ConstantTexture(Vector3(0.96f, 0.1f, 0.1f)));
	Material *greenMat = new Lambertian(new ConstantTexture(Vector3(0.1f, 0.96f, 0.1f)));
	Material *blueMat = new Lambertian(new ConstantTexture(Vector3(0.1f, 0.1f, 0.96f)));
	Material *whiteMat = new Lambertian(new ConstantTexture(Vector3(0.73f, 0.73f, 0.73f)));
	Material *blackMat = new Lambertian(new ConstantTexture(Vector3()));
	Material *light3 = new DiffuseLight(new ConstantTexture(Vector3(1.0f, 1.0f, 1.0f)));

	Mesh *cubeMesh = new Mesh("Resources/cube.obj", new Metal(Vector3(0.47f, 0.98f, 0.59f), 0.85f), 6);
	Mesh *teapotMesh = new Mesh("Resources/utah_teapot.obj", new Lambertian(new ConstantTexture(Vector3(0.5f, 0.6f, 0.2f))), 60);

	Vector3 cameraPosition(0.0f, 3.0f, 3.9f);
	Vector3 lookAtPos(0.0f, 3.0f, 0.0f);
	float distanceToFocus = 10.0f;
	float aperture = 0.0f;
	float vfov = 75.0f;
	uint16_t width = 1024;
	uint16_t height = 1024;

	Camera camera(cameraPosition, lookAtPos, Vector3(0.0f, 1.0f, 0.0f), vfov,
		float(width) / float(height), aperture, distanceToFocus, 0.0f, 1.0f);

	Scene scene;
	scene.Add(new XZRect(-4.0f, 4.0f, -4.0f, 3.0f,  0.0f, true, whiteMat));
	scene.Add(new XZRect(-4.0f, 4.0f, -3.0f, 3.0f,  6.0f, false, whiteMat));
	scene.Add(new XYRect(-4.0f, 4.0f, 0.0f, 6.0f, -4.0f, false, whiteMat));
	scene.Add(new XYRect(-4.0f, 4.0f, 0.0f, 6.0f, 4.0f, false, blackMat));
	scene.Add(new YZRect(0.0f, 7.0f, -4.0f, 4.0f, -3.5f, false, redMat));
	scene.Add(new YZRect(0.0f, 7.0f, -4.0f, 4.0f,  3.5f, true, greenMat));
	scene.Add(cubeMesh);
	scene.Add(teapotMesh);
	scene.Add(new XZRect(-3.0f, 3.0f, -3.5f, -3.0f, 0.0f, true, light3));
	scene.Add(new XZRect(-3.0f, 3.0f, 3.5f, 3.0f, 0.0f, true, light3));
	scene.Add(new XZRect(-3.0f, -2.5f, -3.5f, 3.0f, 0.0f, true, light3));
	scene.Add(new XZRect(2.5f, 3.0f, -3.5f, 3.0f, 0.0f, true, light3));
*/