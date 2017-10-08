#include "Vector3.h"

Vector3 operator+(const Vector3 &lhs, const Vector3 &rhs)
{
	return Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

Vector3 operator-(const Vector3 &lhs, const Vector3 &rhs)
{
	return Vector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

Vector3 operator-(const Vector3 &vec)
{
	return Vector3(-vec.x, -vec.y, -vec.z);
}

Vector3 operator*(const Vector3 &lhs, const Vector3 &rhs)
{
	return Vector3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
}

Vector3 operator*(const float value, const Vector3 &vec)
{
	return Vector3(vec.x * value, vec.y * value, vec.z * value);
}

Vector3 operator*(const Vector3 &vec, const float value)
{
	return Vector3(vec.x * value, vec.y * value, vec.z * value);
}

Vector3 operator/(const Vector3 &vec, const float value)
{
	return Vector3(vec.x / value, vec.y / value, vec.z / value);
}

Vector3& Vector3::operator+=(const Vector3 &v2)
{
	e[0] += v2.e[0];
	e[1] += v2.e[1];
	e[2] += v2.e[2];

	return *this;
}

Vector3& Vector3::operator-=(const Vector3 &v2)
{
	e[0] -= v2.e[0];
	e[1] -= v2.e[1];
	e[2] -= v2.e[2];

	return *this;
}

Vector3& Vector3::operator*=(const Vector3 &v2)
{
	e[0] *= v2.e[0];
	e[1] *= v2.e[1];
	e[2] *= v2.e[2];

	return *this;
}

Vector3& Vector3::operator/=(const Vector3 &v2)
{
	e[0] /= v2.e[0];
	e[1] /= v2.e[1];
	e[2] /= v2.e[2];

	return *this;
}

Vector3& Vector3::operator*=(const float value)
{
	e[0] *= value;
	e[1] *= value;
	e[2] *= value;

	return *this;
}

Vector3& Vector3::operator/=(const float value)
{
	e[0] /= value;
	e[1] /= value;
	e[2] /= value;

	return *this;
}

float Vector3::Length() const
{
	return sqrtf((e[0] * e[0]) + (e[1] * e[1]) + (e[2] * e[2]));
}

float Vector3::LengthSquared() const
{
	return (e[0] * e[0]) + (e[1] * e[1]) + (e[2] * e[2]);
}