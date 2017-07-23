#include "ConstantTexture.h"

ConstantTexture::ConstantTexture() { }

ConstantTexture::ConstantTexture(Vector3 &_color)
	: color(_color)
{

}

Vector3 ConstantTexture::Value(const Vector2 &uv, const Vector3 &p) const
{
	return color;
}