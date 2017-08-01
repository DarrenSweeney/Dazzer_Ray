#include "Light.h"
#include "..\Math\Sampler.h"

class PointLight : public Light 
{
public:
	PointLight();
	PointLight(Vector3 &position, Vector3 &color, float ls);

	Vector3 GetDirection(HitRecord &rec) const override;
	Vector3 L(HitRecord &rec) override;
	bool InShadow(const Ray &ray, const Hitable* hitable) const override;

private:
	Vector3 position;
};