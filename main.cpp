#include "Scene\Scene.h"

int main()
{
	Scene scene;
	{
		PROFILE("Scene::RenderScene");
		scene.RenderScene();
	}

	/*
		@todo(Daren): Going to seperate renderer and scene to have something similar to pt.
		Nice clean layout

		Scene scene;
		Material *material = new Metal(Vector3(1.0f, 1.0f, 1.0f), 0.9f);
		Material *material2 = new Lambertian(new ConstantTexture(Vector3(0.9f, 0.5f, 1.0f)));
		Material *redMat = new Lambertian(new ConstantTexture(Vector3(0.96f, 0.1f, 0.1f)));
		Material *greenMat = new Lambertian(new ConstantTexture(Vector3(0.1f, 0.96f, 0.1f)));
		Material *light = new DiffuseLight(new ConstantTexture(Vector3(1.0f, 1.0f, 1.0f)));

		Hitable disk = new Disk(Vector3(0.0f, -1.0f, 0.0f), UnitVector(Vector3(0.0f, 1.0f, 0.0f)), 4.0f, material);
		hitable sphere = new Sphere(Vector3(-1.5f, 0.0f, 1.5f), 1.0f, material2);
		Hitable light = new Sphere(Vector3(3.5f, 0.5f, 2.0f), 0.5f, light);

		scene.Add(disk);
		scene.Add(sphere);
		scene.Add(light);

		Camera camera = Camera(...);

		Renderer render = new render(scene, camera, 1024, 512, 256, 2);
		render->RenderScene("Scene");

		delete all the stuff!
	*/

	return 0;
}