#ifndef CONSTANT_TEXTURE_H
#define CONSTANT_TEXTURE_H

#include "Texture.h"

class ConstantTexture : public Texture
{
public:
	ConstantTexture();
	ConstantTexture(Vector3 &_color);

	Vector3 Value(const Vector2 &uv, const Vector3 &p) const override;

private:
	Vector3 color;
};

#endif