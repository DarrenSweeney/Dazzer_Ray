#ifndef TEXTURE_H
#define TEXTURE_H

#include "..\Math\Vector3.h"
#include "..\Math\Vector2.h"

class Texture
{
public:
	// Todo(Darren): Remove pure virtual for sphere parameter
	virtual Vector3 Value(const Vector2 &uv, const Vector3 &p) const = 0;
};

#endif