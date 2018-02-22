#pragma once
#include <math.h>
struct Vector2
{
public:
	float x;
	float y;
	Vector2();
	Vector2(float oneP);
	Vector2(float x, float y);
	Vector2 rotate(float angle);
	static Vector2 up();
	static Vector2 down();
	static Vector2 left();
	static Vector2 right();
	friend const Vector2 operator+(const Vector2& lv, const Vector2& rv);
	friend const Vector2 operator+(const Vector2& lv, const float& rf);
	friend const Vector2 operator-(const Vector2& lv, const Vector2& rv);
	friend const Vector2 operator-(const Vector2& lv, const float& rf);
	friend const Vector2 operator/(const Vector2& lv, const float& rf);
	friend const Vector2 operator*(const Vector2& lv, const float& rf);
	friend const Vector2 operator*(const Vector2& lv, const Vector2& rv);
	friend const Vector2& operator+=(Vector2& lv, const Vector2& rv);
	friend const Vector2& operator-=(Vector2& lv, const Vector2& rv);
	~Vector2();
};

