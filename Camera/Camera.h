#ifndef CAMERA_H
#define CAMERA_H

#include "..\Math\Ray.h"
#include "..\Sampler.h"
#include "..\Math\MathUtil.h"

class Camera
{
public:
	Camera();
	Camera(Vector3 &position, Vector3 &lookAt, Vector3 &upVec, float vfov, float aspectRatio,
		float aperature, float focusDistance, float shutterOpenTime, float shutterCloseTune);

	Ray GetRay(float s, float t);

private:
	Vector3 origin;
	Vector3 lowerLeftCorner;
	Vector3 horizontal;
	Vector3 vertical;
	Vector3 u, v, w;
	float lensRadius;
	float shutterOpenTime, shutterCloseTime;
};

#endif
