#pragma once
#include "Vector3.h"
#include <sstream>
#include <math.h>
struct Matrix3 {
	double values [9];
	Matrix3();
	Matrix3(double Values[9]);
	static Matrix3 createRotationX(double rot);
	static Matrix3 createRotationY(double rot);
	static Matrix3 createRotationZ(double rot);
	static Matrix3 createRotation(Vector3 rot);
	friend const Matrix3 operator*(const Matrix3& ml, const Matrix3& mr);
	friend const Vector3 operator*(const Matrix3& ml, const Vector3& vr);
	~Matrix3();
	std::string toString();
};