#include "DazzerRay.h"

int main()
{
	Material *redMat = new Lambertian(new ConstantTexture(Vector3(0.96f, 0.1f, 0.1f)));
	Material *greenMat = new Lambertian(new ConstantTexture(Vector3(0.1f, 0.96f, 0.1f)));
	Material *blueMat = new Lambertian(new ConstantTexture(Vector3(0.1f, 0.1f, 0.96f)));
	Material *whiteMat = new Lambertian(new ConstantTexture(Vector3(0.73f, 0.73f, 0.73f)));
	Material *blackMat = new Lambertian(new ConstantTexture(Vector3()));
	Material *light3 = new DiffuseLight(new ConstantTexture(Vector3(1.0f, 1.0f, 1.0f)));
	Material *redLight = new DiffuseLight(new ConstantTexture(Vector3(0.96f, 0.1f, 0.1f)));

	Mesh *dragonMesh = new Mesh("Resources/Dragon.obj", new Lambertian(new ConstantTexture(Vector3(0.93f, 0.37f, 0.0f))), 200);

	// From below looking above
	//Vector3 cameraPosition(0.0f, 160.0f, 140.0f);
	//Vector3 lookAtPos(0.0f, 170.0f, 120.0f);

	Vector3 cameraPosition(-2.0f, 2.2f, 0.5f);
	Vector3 lookAtPos(0.25f, 0.45f, -0.12f);
	float distanceToFocus = 3.0f;
	float aperture = 0.01f;
	float vfov = 40.0f;
	uint16_t width = 1024;
	uint16_t height = 512;

	Camera camera(cameraPosition, lookAtPos, Vector3(0.0f, 1.0f, 0.0f), vfov,
		float(width) / float(height), aperture, distanceToFocus, 0.0f, 1.0f);

	Scene scene;
	scene.Add(new Plane(Vector3(0.0f, 0.2f, 0.0f), Vector3(0.0f, 1.0f, 0.0f),
		new Lambertian(new CheckerTexture(new ConstantTexture(Vector3(0.7f, 0.7f, 0.7f)), new ConstantTexture(Vector3())))));
	scene.Add(dragonMesh);
	scene.Add(new XZRect(1.0f, 3.0f, -4.0f, 0.0f, 3.0f, false, light3));
	scene.Add(new Sphere(Vector3(1.3f, 0.8f, -0.0f), 0.6f, new Metal(Vector3(0.9f, 0.9f, 0.85f))));
	scene.Add(new Sphere(Vector3(-0.8f, 1.1f, -0.7f), 0.08f, redLight));

	Renderer renderer(&scene, &camera, width, height, 8, 8);
	renderer.RenderScene();

	return 0;
}

// Statue Lady
/*
	Material *redMat = new Lambertian(new ConstantTexture(Vector3(0.96f, 0.1f, 0.1f)));
	Material *greenMat = new Lambertian(new ConstantTexture(Vector3(0.1f, 0.96f, 0.1f)));
	Material *blueMat = new Lambertian(new ConstantTexture(Vector3(0.1f, 0.1f, 0.96f)));
	Material *whiteMat = new Lambertian(new ConstantTexture(Vector3(0.73f, 0.73f, 0.73f)));
	Material *blackMat = new Lambertian(new ConstantTexture(Vector3()));
	Material *light3 = new DiffuseLight(new ConstantTexture(Vector3(1.0f, 1.0f, 1.0f)));

	Mesh *wingedMesh = new Mesh("Resources/Winged_Victory.obj", new Lambertian(new ConstantTexture(Vector3(0.7f, 0.48f, 0.59f))), 200);

	// From below looking above
	//Vector3 cameraPosition(0.0f, 160.0f, 140.0f);
	//Vector3 lookAtPos(0.0f, 170.0f, 120.0f);

	Vector3 cameraPosition(0.0f, 200.0f, 190.0f);
	Vector3 lookAtPos(0.0f, 200.0f, 120.0f);
	float distanceToFocus = 10.0f;
	float aperture = 0.0f;
	float vfov = 75.0f;
	uint16_t width = 1024;
	uint16_t height = 1024;

	Camera camera(cameraPosition, lookAtPos, Vector3(0.0f, 1.0f, 0.0f), vfov,
	float(width) / float(height), aperture, distanceToFocus, 0.0f, 1.0f);

	Scene scene;
	scene.Add(wingedMesh);
*/

// Cornell Box
/*
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
	scene.Add(new XZRect(-4.0f, 4.0f, -4.0f, 3.0f, 0.0f, true, whiteMat));
	scene.Add(new XZRect(-4.0f, 4.0f, -3.0f, 3.0f, 6.0f, false, whiteMat));
	scene.Add(new XYRect(-4.0f, 4.0f, 0.0f, 6.0f, -4.0f, false, whiteMat));
	//scene.Add(new XYRect(-4.0f, 4.0f, 0.0f, 6.0f, 4.0f, false, blackMat));
	scene.Add(new YZRect(0.0f, 7.0f, -4.0f, 4.0f, -3.5f, false, redMat));
	scene.Add(new YZRect(0.0f, 7.0f, -4.0f, 4.0f, 3.5f, true, greenMat));
	scene.Add(cubeMesh);
	scene.Add(teapotMesh);
	scene.Add(new XZRect(-3.0f, 3.0f, -3.5f, -3.0f, 0.0f, true, light3));
	scene.Add(new XZRect(-3.0f, 3.0f, 3.5f, 3.0f, 0.0f, true, light3));
	scene.Add(new XZRect(-3.0f, -2.5f, -3.5f, 3.0f, 0.0f, true, light3));
	scene.Add(new XZRect(2.5f, 3.0f, -3.5f, 3.0f, 0.0f, true, light3));

	Renderer renderer(&scene, &camera, width, height, 1, 8);
	renderer.RenderScene();
*/