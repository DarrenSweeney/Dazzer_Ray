#ifndef SCENE_H
#define SCENE_H

#include "..\Objects\HitableList.h"

struct Scene
{
	HitableList sceneObects;
	void Add(Hitable *hitable);
};

#endif