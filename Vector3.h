#pragma once

/// <summary>
///������� ����� �������������� ����� � ���������� ������������, � ��������� �������� ��� � ����������
/// </summary>
struct Vector3
{
	float x;
	float y;
	float z;
	Vector3();
	Vector3(float x, float y, float z);
	Vector3(float oneSize);
	Vector3 Normalized();
	void normalize();
	float length();
	float scalar(Vector3 v2);
	float mod();
	static float distance(Vector3 v1, Vector3 v2);
	friend const Vector3 operator+(const Vector3& lv, const Vector3& rv);
	friend const Vector3 operator +(const Vector3& v1, const float& f);
	friend const Vector3 operator -(const Vector3& v1, const Vector3& v2);
	friend const Vector3 operator -(const Vector3& v1, const float& f);
	friend const Vector3 operator *(const Vector3& v1, const Vector3& v2);
	friend const Vector3 operator *(const Vector3& v1, const float& f);
	friend const Vector3 operator /(const Vector3& v1, const Vector3& v2);
	friend const Vector3 operator /(const Vector3& v1, const float& f);
	friend const Vector3& operator+=(Vector3& lv, const Vector3& rv);
	friend const Vector3& operator-=(Vector3& lv, const Vector3& rv);
	static Vector3 zero();

	/// <summary>
	/// forward
	/// </summary>
	static Vector3 fwd();

	/// <summary>
	/// backward
	/// </summary>
	static Vector3 bwd();

	static Vector3 up();
	static Vector3 down();
	static Vector3 left();
	static Vector3 right();
};