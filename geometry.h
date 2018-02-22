#pragma once

#include <vector>
#include <Windows.h>
#include <algorithm>

#include "Vector3.h"
#include "Matrix3.h"
#include "Vector2.h"

#define PI 3.1415926535897932384626433832795
using namespace std;

void fill(HDC hdc, Vector3 figurer[], int points, HPEN pen);

class figure {
public:
	double zIndex;
	vector<Vector3> points = vector<Vector3>();
	COLORREF color;
	Vector3 normal;
	figure();
	virtual void draw(HDC hdc, bool fil, Vector3 _center, Vector3 sCenter, Matrix3 _rotation, float _scale, std::vector<figure> * polys, int index, Vector3 light);
	void figure::drawShadow(HDC hdc, bool fil, Vector3 _center, Vector3 sCenter, Matrix3 _rotation, float _scale, std::vector<figure> * polys, int plane, Vector3 light,int index);
	virtual bool operator > (figure const &t);
	virtual bool operator < (figure const &t);
	virtual bool operator == (figure const &t);
	~figure();
};

class triangle : public figure
{
public:
	triangle(Vector3 A, Vector3 B, Vector3 C, COLORREF Color);
};

class poly : public figure
{
public:
	poly(Vector3 a, Vector3 b, Vector3 c, Vector3 d, COLORREF Color);
	
};

class Edge
{
public:
	double ymin, ymax, xstart, xchange;
	short way;
	bool destroy = false;
	Edge(Vector3 a, Vector3  b);
	bool operator > (Edge const &e);
	bool operator < (Edge const &e);
	bool operator == (Edge const &e);
};

class object
{
public:
	std::vector<figure> polys;
	object();
	object(std::vector<figure> figures, Vector3 center, float scale, bool shadow = true);
	void Draw(HDC hdc, Vector3 light);
	void DrawShadow(HDC hdc, int plane, Vector3 light);
	void move(Vector3 wher);
	void addScale(float how);
	void addRot(Vector3 rot);
	void setScenter(Vector3 sCenter);
	Vector3 getCenter() { return _center; }
private:
	bool _shadow;
	Vector3 _center;
	Vector3 _rotation;
	Vector3 _sCenter;
	float _scale;
};