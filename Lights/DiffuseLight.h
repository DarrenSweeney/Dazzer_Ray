#ifndef DIFFUSE_LIGHT_H
#define DIFFUSE_LIGHT_H

#include "..\Materials\Material.h"
#include "..\Textures\Texture.h"

class DiffuseLight : public Material
{
public:
	DiffuseLight(Texture *texture);

	bool Scatter(const Ray &rayIn, const HitRecord &hitRecord, Vector3 &attenuation, Ray &scattered) const override;
	Vector3 Emitted(Vector2 uv, const Vector3 &p) const override;

private:
	Texture *emitTexture;
};

#endif