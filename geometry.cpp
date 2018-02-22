#include "geometry.h"

void fill(HDC hdc, Vector3 figurer[], int points, HPEN pen)
{
	vector<Edge> edges = vector<Edge>();
	Vector3 tmp = figurer[0];
	for (int i = 1; i <= points; i++)
	{
		edges.push_back(Edge(tmp, figurer[i == points ? 0 : i]));
		tmp = figurer[i];
	}

	sort(edges.begin(), edges.end());

	for (unsigned int i = 0; i < edges.size();)
	{
		if (edges.at(i).destroy)
			edges.erase(edges.begin() + i);
		else i++;
	}

	if (0 == edges.size()) return;
	vector<Edge> activeEdges = vector<Edge>();
	activeEdges.push_back(edges.at(0));

	unsigned int edgeId = 0;
	for (unsigned int i = 1; i < edges.size(); edgeId = i, i++)
	{
		if (activeEdges.at(0) == edges.at(i))
			activeEdges.push_back(edges.at(i));
		else break;
	}

	int line = activeEdges.at(0).ymin + 1;
	while (activeEdges.size() > 1)
	{
		for (unsigned int i = 0; i < activeEdges.size();)
		{
			if (activeEdges.at(i).ymax <= line)
				activeEdges.erase(activeEdges.begin() + i);
			else i++;
		}

		for (unsigned int i = edgeId + 1; i < edges.size(); edgeId = i, i++)
			if (edges.at(i).ymin <= line)
				activeEdges.push_back(edges.at(i));
			else break;

			if (activeEdges.size() < 2) return;

			Edge ae = activeEdges.at(0);
			Vector2 a = Vector2(ae.xstart + (line - ae.ymin)*ae.xchange * ae.way, line);
			ae = activeEdges.at(1);
			Vector2 b = Vector2(ae.xstart + (line - ae.ymin)*ae.xchange * ae.way, line);

			SelectObject(hdc, pen);
			MoveToEx(hdc, a.x, a.y, NULL);
			LineTo(hdc, b.x, b.y);
			line++;
	}
}

#pragma region figure

figure::figure() {};

void figure::draw(HDC hdc, bool fil, Vector3 _center, Vector3 sCenter, Matrix3 _rotation, float _scale, std::vector<figure> * polys, int index, Vector3 light)
{
	int l = points.size();

	Vector3 n =_rotation*normal;
	float radian = 180 / PI;
	float scalar = n.scalar(light.Normalized());
	float mod = n.mod()*light.Normalized().mod();
	float degree = acos(scalar / mod)*radian;


	float depth = 1 - abs(degree) / 90 / 2;
	depth = depth > 1 || depth < 0 ? 0 : depth;

	HPEN pen = CreatePen(PS_SOLID, 1, RGB(GetRValue(color)*depth, GetGValue(color)*depth, GetBValue(color)*depth));
	Vector3* figurer = new Vector3[l];
	zIndex = 0;
	for (unsigned int i = 0; i < l; i++)
	{
		Vector3 a = (_rotation * points.at(i) * _scale) + _center;
		Vector3 b = (_rotation * points.at(i >= (l - 1) ? 0 : (i + 1)) * _scale) + _center;
		zIndex += a.z;
		if (a.z > 0 && b.z > 0) {
			float scale = (a.z / 100);
			a = ((a - sCenter) / (a.z / 500)) + sCenter;
			scale = (b.z / 100);
			b = ((b - sCenter) / (b.z / 500)) + sCenter;
			figurer[i] = a;
			SelectObject(hdc, pen);
			MoveToEx(hdc, floor(a.x), floor(a.y), NULL);
			LineTo(hdc, floor(b.x), floor(b.y));
			//drawBrezinhem(hdc, floor(a.x), floor(a.y), floor(b.x), floor(b.y));
		}
	}
	polys->at(index).zIndex = zIndex;
	if (fil)
		fill(hdc, figurer, l, pen);
	DeleteObject(pen);
	delete[] figurer;
}

void figure::drawShadow(HDC hdc, bool fil, Vector3 _center, Vector3 sCenter, Matrix3 _rotation, float _scale, std::vector<figure> * polys, int plane, Vector3 light, int index)
{
	int l = points.size();
	HPEN pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	Vector3* figurer = new Vector3[l];
	zIndex = 0;
	for (unsigned int i = 0; i < l; i++)
	{
		Vector3 a = (_rotation * points.at(i) * _scale) + _center;
		Vector3 shadow = a - light;
		int distance = Vector3::distance(a, Vector3(a.x, plane, a.z));
		a += shadow * (distance / shadow.y);

		Vector3 b = (_rotation * points.at(i >= (l - 1) ? 0 : (i + 1)) * _scale) + _center;
		shadow = b - light;
		b += shadow * (Vector3::distance(b, Vector3(b.x, plane, b.z)) / shadow.y);

		a.y = plane;
		b.y = plane;

		if (a.z > 0 && b.z > 0) {
			float scale = (a.z / 100);
			a = ((a - sCenter) / (a.z / 500)) + sCenter;
			scale = (b.z / 100);
			b = ((b - sCenter) / (b.z / 500)) + sCenter;
			figurer[i] = a;
			SelectObject(hdc, pen);
			MoveToEx(hdc, floor(a.x), floor(a.y), NULL);
			LineTo(hdc, floor(b.x), floor(b.y));
			//drawBrezinhem(hdc, floor(a.x), floor(a.y), floor(b.x), floor(b.y));
		}
	}
	if (fil)
		fill(hdc, figurer, l, pen);
	DeleteObject(pen);
	delete[] figurer;
}

bool figure::operator < (figure const &t)
{
	return zIndex > t.zIndex;
}

bool figure::operator > (figure const &t)
{
	return zIndex < t.zIndex;
}

bool figure::operator == (figure const &t)
{
	return zIndex == t.zIndex;
}

figure::~figure()
{

}

#pragma endregion

triangle::triangle(Vector3 A, Vector3 B, Vector3 C, COLORREF Color)
{
	points.push_back(A);
	points.push_back(B);
	points.push_back(C);
	color = Color;
	zIndex = 0;
}

poly::poly(Vector3 a, Vector3 b, Vector3 c, Vector3 d, COLORREF Color)
{
	points.push_back(a);
	points.push_back(b);
	points.push_back(c);
	points.push_back(d);
	color = Color;
	zIndex = 0;
}

#pragma region Edge
Edge::Edge(Vector3 a, Vector3  b) {
	if (b.y == a.y) { destroy = true; return; }

	xchange = abs(a.x - b.x) / abs(a.y - b.y);

	if (a.y < b.y)
	{
		ymin = a.y;
		ymax = b.y;
		xstart = a.x;
		way = a.x < b.x ? 1 : (-1);
	}
	else
	{
		ymin = b.y;
		ymax = a.y;
		xstart = b.x;
		way = a.x > b.x ? 1 : (-1);
	}
}

bool Edge::operator > (Edge const &e)
{
	return ymin > e.ymin;
}

bool Edge::operator < (Edge const &e)
{
	return ymin < e.ymin;
}

bool Edge::operator == (Edge const &e)
{
	return ymin == e.ymin;
}
#pragma endregion

#pragma region object
object::object() {};
object::object(vector<figure> figures, Vector3 center, float scale, bool shadow)
{
	_shadow = shadow;
	polys = figures;
	_center = center;
	_scale = scale;
	Vector3 normal = Vector3(0);
	int count = 0;
	for (int i = 0; i < polys.size(); i++)
	{
		for (Vector3 point : polys[i].points)
		{
			normal += point;
			count++;
		}
		polys[i].normal = normal / count;
		polys[i].normal.normalize();
		normal = Vector3(0);
		count = 0;
	}
};
void object::Draw(HDC hdc, Vector3 light) {
	Matrix3 rotation = Matrix3::createRotation(_rotation);
	int i = 0;
	for each(figure f in polys)
	{
		f.draw(hdc, true, _center, _sCenter, rotation, _scale, &polys, i, light);
		i++;
	}
	std::sort(polys.begin(), polys.end());
	rotation.~Matrix3();
}

void object::DrawShadow(HDC hdc, int plane, Vector3 light)
{
	if (_shadow) {
		Matrix3 rotation = Matrix3::createRotation(_rotation);
		int i = 0;
		for each(figure f in polys)
		{
			f.drawShadow(hdc, true, _center, _sCenter, rotation, _scale, &polys, plane, light, i);
			i++;
		}
		std::sort(polys.begin(), polys.end());
		rotation.~Matrix3();
	}
}

void object::move(Vector3 wher)
{
	_center += wher;
}

void object::addScale(float how)
{
	_scale += how;
	if (_scale < 0) _scale = 0.00000000000000001;
}

void object::addRot(Vector3 rot)
{
	_rotation += rot;
}

void object::setScenter(Vector3 sCenter)
{
	_sCenter = sCenter;
}

#pragma endregion