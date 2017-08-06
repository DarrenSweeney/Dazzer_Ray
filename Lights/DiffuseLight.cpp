#include "DiffuseLight.h"

DiffuseLight::DiffuseLight(Texture *texture)
	: emitTexture(texture)
{

}

bool DiffuseLight::Scatter(const Ray &rayIn, const HitRecord &hitRecord, Vector3 &attenuation, Ray &scattered) const
{
	return false;
}

Vector3 DiffuseLight::Emitted(Vector2 uv, const Vector3 &p) const
{
	return emitTexture->Value(uv, p);
}