#include "Scene.h"

void Scene::Add(Hitable *hitable)
{
	sceneObects.Add(hitable);
}