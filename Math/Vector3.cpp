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

inline void Vector3::UnitVector()
{
	*this = *this / this->Lenght();
}

Vector3 UnitVector(const Vector3 &vec)
{
	return vec / vec.Lenght();
}

Vector3 Reflect(const Vector3 &v, const Vector3 &n)
{
	return v - 2 * Dot(v, n) * n;
}

float Dot(const Vector3 &v1, const Vector3 &v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector3 Cross(const Vector3 &v1, const Vector3 &v2)
{
	return Vector3((v1.y * v2.z - v1.z * v2.y),
		(-(v1.x * v2.z - v1.z * v2.x)),
		(v1.x * v2.y - v1.y * v2.x));
}