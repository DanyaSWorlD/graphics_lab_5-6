#include "vector2.h"



Vector2::Vector2()
{
}

Vector2::Vector2(float oneP)
{
	x = oneP;
	y = oneP;
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2 Vector2::rotate(float angle)
{
	Vector2 rotated(0);
	rotated.x = this->x * cos(angle) - this->y * sin(angle);
	rotated.y = this->x * sin(angle) + this->y * cos(angle);
	return rotated;
}

Vector2 Vector2::up()
{
	return Vector2(0,-1);
}

Vector2 Vector2::down()
{
	return Vector2(0,1);
}

Vector2 Vector2::left()
{
	return Vector2(-1,0);
}

Vector2 Vector2::right()
{
	return Vector2(1,0);
}

const Vector2 operator+(const Vector2 & lv, const Vector2 & rv)
{
	return Vector2(lv.x+rv.x,lv.y+rv.y);
}

const Vector2 operator+(const Vector2 & lv, const float & rf)
{
	return Vector2(lv.x+rf,lv.y+rf);
}

const Vector2 operator-(const Vector2 & lv, const Vector2 & rv)
{
	return Vector2(lv.x-rv.x, lv.y-rv.y);
}

const Vector2 operator-(const Vector2 & lv, const float & rf)
{
	return Vector2(lv.x-rf,lv.y-rf);
}

const Vector2 operator/(const Vector2 & lv, const float & rf)
{
	return Vector2(lv.x/rf,lv.y/rf);
}

const Vector2 operator*(const Vector2 & lv, const float & rf)
{
	return Vector2(lv.x * rf, lv.y * rf);
}

const Vector2 operator*(const Vector2 & lv, const Vector2 & rv)
{
	return Vector2(lv.x*rv.x,lv.y*rv.y);
}

const Vector2& operator+=(Vector2 & lv, const Vector2 & rv)
{
	lv.x += rv.x;
	lv.y += rv.y;
	return lv;
}

const Vector2& operator-=(Vector2 & lv, const Vector2 & rv)
{
	Vector2 v = lv-rv;
	lv.x = v.x;
	lv.y = v.y;
	return lv;
}


Vector2::~Vector2()
{
}

