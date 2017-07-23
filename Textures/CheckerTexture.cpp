#include "CheckerTexture.h"

CheckerTexture::CheckerTexture() { }

CheckerTexture::CheckerTexture(Texture *t0, Texture *t1)
	: odd(t0), even(t1)
{

}

Vector3 CheckerTexture::Value(const Vector2 &uv, const Vector3 &p) const
{
	float sines = sinf(10 * p.x) * sinf(10 * p.y) * sinf(10 * p.z);

	if (sines < 0)
		return odd->Value(uv, p);
	else
		return even->Value(uv, p);
}