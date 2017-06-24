#ifndef CHECKER_TEXTURE_H
#define CHECKER_TEXTURE_H

#include "Texture.h"

class CheckerTexture : public Texture
{
public:
	CheckerTexture();
	CheckerTexture(Texture *t0, Texture *t1);

	Vector3 Value(const Vector2 &uv, const Vector3 &p) const override;

private:
	Texture *odd;
	Texture *even;
};

#endif