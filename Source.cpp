#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <thread>
#include <math.h>
#include <vector>
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix3.h"
#include <algorithm>
#include <chrono>
#include "geometry.h"

#define WHITE RGB(255,255,255)
#define RED RGB(255,0,0)
#define GREEN RGB(0,255,0)
#define BLUE RGB(0,0,255)
#define YELLOW RGB(255,255,0)
#define PURPLE RGB(0,100,100)


using namespace std::chrono;

static std::vector<char> mVector;
int find(char c)
{
	for (int i = 0; i < mVector.size(); i++)
		if (mVector[i] == c)
			return i;

	return -1;
}

static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (wParam == WM_KEYDOWN) {
		KBDLLHOOKSTRUCT * pkhs = (KBDLLHOOKSTRUCT *)lParam;
		if (find(pkhs->vkCode) == -1)
			mVector.push_back(pkhs->vkCode);
	}
	if (wParam == WM_KEYUP) {
		KBDLLHOOKSTRUCT * pkhs = (KBDLLHOOKSTRUCT *)lParam;
		int p = find(pkhs->vkCode);
		if (p != -1)
		{
			std::vector<char>::iterator pos = mVector.begin() + p;
			mVector.erase(pos);
		}
	}
	PostQuitMessage(0);
	return CallNextHookEx(0, nCode, wParam, lParam);

}

class Runnable
{
public:
	Runnable(HWND hwnd)
	{
		this->hWnd = hwnd;
	}
	void operator()()
	{
		HHOOK g_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);
		MSG msg;
		while (1)
			GetMessage(&msg, hWnd, 0, 0);
		UnhookWindowsHookEx(g_hHook);
	}
private:
	HWND hWnd;
};

void fill(HDC hdc, Vector3 figurer[], int points, HPEN pen);
//void drawBrezinhem(HDC hdc, int x0, int y0, int x1, int y1);

int workingObj;

Vector3 center;
float deltatime = 1;
Vector3 SCenter(0, 0, 0);
float moveFactor = 4;

std::vector<object> objects = std::vector<object>();

/*void drawBrezinhem(HDC hdc, int x0, int y0, int x1, int y1)
{
	int dx = (x1 > x0) ? (x1 - x0) : (x0 - x1);
	int dy = (y1 > y0) ? (y1 - y0) : (y0 - y1);
	int sx = (x1 >= x0) ? (1) : (-1);
	int sy = (y1 >= y0) ? (1) : (-1);
	if (dy < dx)
	{
		int d = (dy << 1) - dx;
		int d1 = dy << 1;
		int d2 = (dy - dx) << 1;
		SetPixel(hdc, x0, y0, RED);
		int x = x0 + sx;
		int y = y0;
		for (int i = 1; i <= dx; i++)
		{
			if (d > 0)
			{
				d += d2;
				y += sy;
			}
			else
				d += d1;
			SetPixel(hdc, x, y, RED);
			x += sx;
		}
	}
	else
	{
		int d = (dx << 1) - dy;
		int d1 = dx << 1;
		int d2 = (dx - dy) << 1;
		SetPixel(hdc, x0, y0, RED);
		int x = x0;
		int y = y0 + sy;
		for (int i = 1; i <= dy; i++)
		{
			if (d > 0)
			{
				d += d2;
				x += sx;
			}
			else
				d += d1;
			SetPixel(hdc, x, y, RED);
			y += sy;
		}
	}

}*/


Vector3 light = Vector3(0, -200, 0);
void DRAW(HDC hdc, int plane)
{
	for (int i = 0; i < objects.size(); i++)
		objects.at(i).DrawShadow(hdc, plane,light);
	for (int i = 0; i < objects.size(); i++)
		objects.at(i).Draw(hdc,light);
}


#pragma region CONTROL

#pragma region MOVEMENT

void moveLeft()
{
	(objects.at(workingObj)).move(Vector3::left() * deltatime * moveFactor);
}


void moveRight()
{
	(objects.at(workingObj)).move(Vector3::right() * deltatime * moveFactor);
}


void moveUp()
{
	(objects.at(workingObj)).move(Vector3::up() * deltatime * moveFactor);
}

void moveDown()
{
	objects.at(workingObj).move(Vector3::down() * deltatime * moveFactor);
}

void moveFwd()
{
	objects.at(workingObj).move(Vector3::fwd() * deltatime * moveFactor);
}

void moveBwd()
{
	objects.at(workingObj).move(Vector3::bwd() * deltatime * moveFactor);
}

#pragma endregion

#pragma region ROTATION

void rotLeft()
{
	objects.at(workingObj).addRot(Vector3::up() * (3.14 / 180 * deltatime));
}

void rotRight()
{
	objects.at(workingObj).addRot(Vector3::down() * (3.14 / 180 * deltatime));
}

void rotUp()
{
	objects.at(workingObj).addRot(Vector3::left() * (3.14 / 180 * deltatime));
}

void rotDown()
{
	objects.at(workingObj).addRot(Vector3::right() * (3.14 / 180 * deltatime));
}

void rotZP()
{
	objects.at(workingObj).addRot(Vector3::fwd() * (3.14 / 180 * deltatime));
}

void rotZM()
{
	objects.at(workingObj).addRot(Vector3::bwd() * (3.14 / 180 * deltatime));
}

#pragma endregion

void chObj()
{
	if (objects.size() > workingObj + 1)
		workingObj++;
	else
		workingObj = 0;
}

void scaleUp()
{
	objects.at(workingObj).addScale(0.01 * deltatime);
}

void scaleDown()
{
	objects.at(workingObj).addScale(-0.01 * deltatime);
}

#pragma endregion

void drawWholeScreen(HDC hdc, int width, int height, HPEN pen)
{
	SelectObject(hdc, pen);
	for (int j = 0; j < height; j++) {
		MoveToEx(hdc, 0, j, NULL);
		LineTo(hdc, width, j);
	}
}

int main(int)
{
	std::vector<figure> polys = std::vector<figure>();
	Vector3 points[]{
		Vector3::up() * 50 + Vector3::left() * 50 + Vector3::fwd() * 50,
		Vector3::up() * 50 + Vector3::right() * 50 + Vector3::fwd() * 50,
		Vector3::up() * 50 + Vector3::right() * 50 + Vector3::bwd() * 50,
		Vector3::up() * 50 + Vector3::left() * 50 + Vector3::bwd() * 50,
		Vector3::down() * 50 + Vector3::left() * 50 + Vector3::fwd() * 50,
		Vector3::down() * 50 + Vector3::right() * 50 + Vector3::fwd() * 50,
		Vector3::down() * 50 + Vector3::right() * 50 + Vector3::bwd() * 50,
		Vector3::down() * 50 + Vector3::left() * 50 + Vector3::bwd() * 50
	};
	polys.push_back(poly(points[0], points[1], points[2], points[3], GREEN));
	polys.push_back(poly(points[0], points[1], points[5], points[4], GREEN));
	polys.push_back(poly(points[1], points[2], points[6], points[5], GREEN));
	polys.push_back(poly(points[2], points[3], points[7], points[6], GREEN));
	polys.push_back(poly(points[3], points[0], points[4], points[7], GREEN));
	polys.push_back(poly(points[4], points[5], points[6], points[7], RED));

	HWND hWnd = GetConsoleWindow();
	HDC hDC = GetDC(hWnd);

	RECT rect;

	HPEN pen1 = CreatePen(PS_SOLID, 1, RED);
	HPEN pen2 = CreatePen(PS_SOLID, 1, WHITE);

	Runnable r(hWnd);
	std::thread th(r);

	GetClientRect(hWnd, &rect);

	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	center = Vector3(width / 2, height / 2, 0);
	objects.push_back(object(polys, center + Vector3::fwd()*500, 0.1, false));
	objects.push_back(object(polys, center + Vector3::left() * (width / 4) + Vector3::fwd() * 500, 1));
	objects.push_back(object(polys, center + Vector3::right() * (width / 4) + Vector3::fwd() * 500, 1));

	while (1)
	{
		milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

		for (int i = 0; i < mVector.size(); i++)
		{
			char ch = mVector[i];
			switch (ch)
			{
			case 'A':
				moveLeft();
				break;
			case 'D':
				moveRight();
				break;
			case 'W':
				moveUp();
				break;
			case 'S':
				moveDown();
				break;
			case 'Q':
				moveFwd();
				break;
			case 'E':
				moveBwd();
				break;
			case 'Z':
				scaleDown();
				break;
			case 'X':
				scaleUp();
				break;
			case 'F':
				rotLeft();
				break;
			case 'H':
				rotRight();
				break;
			case 'T':
				rotUp();
				break;
			case 'G':
				rotDown();
				break;
			case 'R':
				rotZM();
				break;
			case 'Y':
				rotZP();
				break;
			case 'O':
				chObj();
				break;
			}
		}

		GetClientRect(hWnd, &rect);

		width = rect.right - rect.left;
		height = rect.bottom - rect.top;

		light = objects[0].getCenter() + Vector3::down()*51;
		SCenter = SCenter * Vector3::fwd() + Vector3(width / 2, height / 2, 0);
		for (int i = 0; i < objects.size(); i++) objects.at(i).setScenter(SCenter);

		HDC hMemDC = CreateCompatibleDC(hDC);
		HBITMAP hMemBitmap = CreateCompatibleBitmap(hDC, width, height);

		SelectObject(hMemDC, hMemBitmap);

		drawWholeScreen(hMemDC, width, height, pen2);
		DRAW(hMemDC,height - height/5);
		BitBlt(hDC, 0, 0, width, height, hMemDC, 0, 0, SRCCOPY);

		DeleteObject(hMemBitmap);
		DeleteDC(hMemDC);
		milliseconds ms2 = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
		deltatime = (ms2 - ms).count() / 16.7f;
	}


	getch();
	DeleteObject(pen1);
	DeleteObject(pen2);
	ReleaseDC(hWnd, hDC);
	th.~thread();
	return 0;
}