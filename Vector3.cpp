#include "Vector3.h"
#include <math.h>


Vector3::Vector3()
{
	x = 0;
	y = 0;
	z = 0;
}
Vector3::Vector3(float X, float Y, float Z)
{
	x = X;
	y = Y;
	z = Z;
}

Vector3::Vector3(float oneSize)
{
	x = oneSize;
	y = oneSize;
	z = oneSize;
}

void Vector3::normalize()
{
	Vector3 n = Normalized();
	x = n.x;
	y = n.y;
	z = n.z;
}

Vector3 Vector3::Normalized()
{
	float length = Vector3::length();
	return Vector3(
		x / length,
		y / length,
		z / length
	);
}

float Vector3::length()
{
	return (float)sqrt(x * x + y * y + z * z);
}

float Vector3::distance(Vector3 v1, Vector3 v2)
{
	v1 = v2 - v1;
	return v1.length();
}

float Vector3::scalar(Vector3 v2)
{
	return(x*v2.x + y*v2.y + z*v2.z);
}

float Vector3::mod()
{
	return sqrt(x*x + y*y + z*z);
}

const Vector3 operator+(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

const Vector3 operator +(const Vector3& v1, const float& f)
{
	return Vector3(v1.x + f, v1.y + f, v1.z + f);
}

const Vector3 operator -(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

const Vector3 operator -(const Vector3& v1, const float& f)
{
	return Vector3(v1.x - f, v1.y - f, v1.z - f);
}

const Vector3 operator *(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

const Vector3 operator *(const Vector3& v1, const float& f)
{
	return Vector3(v1.x * f, v1.y * f, v1.z * f);
}

const Vector3 operator /(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
}

const Vector3 operator /(const Vector3& v1, const float& f)
{
	return Vector3(v1.x / f, v1.y / f, v1.z / f);
}

const Vector3& operator+=(Vector3& lv, const Vector3& rv)
{
	lv.x += rv.x;
	lv.y += rv.y;
	lv.z += rv.z;
	return lv;
}

const Vector3& operator-=(Vector3& lv, const Vector3& rv)
{
	lv.x -= rv.x;
	lv.y -= rv.y;
	lv.z -= rv.z;
	return lv;
}

Vector3 Vector3::zero() { return Vector3(0); }
Vector3 Vector3::fwd() { return Vector3(0, 0, 1); }
Vector3 Vector3::bwd() { return Vector3(0, 0, -1); }
Vector3 Vector3::up() { return Vector3(0, -1, 0); }
Vector3 Vector3::down() { return Vector3(0, 1, 0); }
Vector3 Vector3::left() { return Vector3(-1, 0, 0); }
Vector3 Vector3::right() { return Vector3(1, 0, 0); }
