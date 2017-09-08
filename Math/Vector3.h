#ifndef VECTOR3_H
#define VECTOR3_H

#include <math.h>

class Vector3
{
public:
	union
	{
		struct { float x, y, z; };
		struct { float r, g, b; };

		float e[3];
	};

	Vector3(float e1, float e2, float e3) { e[0] = e1; e[1] = e2; e[2] = e3; }
	Vector3() { e[0] = e[1] = e[2] = 0; };

	inline float operator[](int i) const { return e[i]; }
	friend Vector3 operator+(const Vector3 &lhs, const Vector3 &rhs);
	friend Vector3 operator-(const Vector3 &lhs, const Vector3 &rhs);
	friend Vector3 operator-(const Vector3 &vec);
	friend Vector3 operator*(const Vector3 &lhs, const Vector3 &rhs);
	friend Vector3 operator/(const Vector3 &lhs, const Vector3 &rhs);
	friend Vector3 operator*(const Vector3 &vec, const float value);
	friend Vector3 operator*(const float value, const Vector3 &vec);
	friend Vector3 operator/(const Vector3 &vec, const float value);

	Vector3& operator+=(const Vector3 &v2);
	Vector3& operator-=(const Vector3 &v2);
	Vector3& operator*=(const Vector3 &v2);
	Vector3& operator/=(const Vector3 &v2);
	Vector3& operator*=(const float value);
	Vector3& operator/=(const float value);

	float Lenght() const;
	float LengthSquared() const;
};

inline float Dot(const Vector3 &v1, const Vector3 &v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline Vector3 Reflect(const Vector3 &v, const Vector3 &n)
{
	return v - 2 * Dot(v, n) * n;
}

inline Vector3 UnitVector(const Vector3 &vec)
{
	return vec / vec.Lenght();
}

inline Vector3 Cross(const Vector3 &v1, const Vector3 &v2)
{
	return Vector3((v1.y * v2.z - v1.z * v2.y),
		(-(v1.x * v2.z - v1.z * v2.x)),
		(v1.x * v2.y - v1.y * v2.x));
}

inline Vector3 Lerp(const Vector3 &v1, const Vector3 &v2, float t)
{
	return (1.0f - t) * v1 + (t * v2);
}

#endif