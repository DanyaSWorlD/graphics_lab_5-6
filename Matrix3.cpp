#include "Matrix3.h"

using namespace std;

Matrix3::Matrix3() {}
Matrix3::Matrix3(double Values[9])
{
	for (int i = 0; i < 9; i++)
		values[i] = Values[i];
}

Matrix3 Matrix3::createRotationX(double rot)
{
	double d[9]{
		1,0,0,
		0,cos(rot),-sin(rot),
		0,sin(rot),cos(rot)
	};
	return Matrix3(d);
}

Matrix3 Matrix3::createRotationY(double rot)
{
	double d[9]{
		cos(rot),0,sin(rot),
		0,1,0,
		-sin(rot),0,cos(rot)
	};
	return Matrix3(d);
}

Matrix3 Matrix3::createRotationZ(double rot)
{
	double d[9]{
		cos(rot),-sin(rot),0,
		sin(rot),cos(rot),0,
		0,0,1
	};
	return Matrix3(d);
}

Matrix3 Matrix3::createRotation(Vector3 rot)
{
	return Matrix3::createRotationX(rot.x) * Matrix3::createRotationY(rot.y) * Matrix3::createRotationZ(rot.z);
}

const Matrix3 operator*(const Matrix3& ml, const Matrix3& mr)
{
	double val[9];
	for (int i = 0; i < 9; i++)
	{
		double summ = 0;
		for (int j = 0; j < 3; j++)
			summ += ml.values[(i / 3) * 3 + j] * mr.values[(i % 3) + j * 3];
		val[i] = summ;
	}

	return Matrix3(val);
	
}

const Vector3 operator*(const Matrix3& ml, const Vector3& vr)
{
	return Vector3(ml.values[0] * vr.x + ml.values[1] * vr.y + ml.values[2] * vr.z,
		ml.values[3] * vr.x + ml.values[4] * vr.y + ml.values[5] * vr.z,
		ml.values[6] * vr.x + ml.values[7] * vr.y + ml.values[8] * vr.z);
}

Matrix3::~Matrix3()
{
}

string Matrix3::toString()
{
	stringstream ss;
	string s;
	string sb;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++) {
			ss << values[(i * 3) + j];
			ss >> sb;
			s += sb;
			s += "    ,";
		}
		s += "\n";
	}
	return s;
}