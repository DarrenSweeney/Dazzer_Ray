#include "Camera.h"

Camera::Camera() { }

Camera::Camera(Vector3 &position, Vector3 &lookAt, Vector3 &upVec, float vfov, float aspectRatio,
	float aperature, float focusDistance, float shutterOpenTime, float shutterCloseTime)
{
	this->shutterOpenTime = shutterOpenTime;
	this->shutterCloseTime = shutterCloseTime;
	lensRadius = aperature / 2;
	float theta = vfov * PI / 180.0f;
	float halfHeight = tan(theta / 2);
	float halfWidth = aspectRatio * halfHeight;
	origin = position;
	w = UnitVector(position - lookAt);
	u = UnitVector(Cross(upVec, w));
	v = Cross(w, u);

	lowerLeftCorner = origin - halfWidth * focusDistance * u
		- halfHeight * focusDistance * v - focusDistance * w;
	horizontal = 2 * halfWidth * focusDistance * u;
	vertical = 2 * halfHeight * focusDistance * v;
}

Ray Camera::GetRay(float s, float t)
{
	Vector3 rd = lensRadius * RandomInUnitDisk();
	Vector3 offset = u * rd.x + v * rd.y;
	float time = shutterOpenTime + randF(0.0f, 1.0f) * (shutterCloseTime - shutterOpenTime);

	return Ray(origin + offset, lowerLeftCorner + s * horizontal + t * vertical - origin - offset, time);
}