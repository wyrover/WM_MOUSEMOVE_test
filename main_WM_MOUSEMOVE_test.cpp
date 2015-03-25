//
// main_WM_MOUSEMOVE_test.cpp - WM_MOUSEMOVEはどのぐらいの頻度で飛んでくるか？チェックプログラム
//
#pragma once

#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Windowsx.h>

#include "resource.h"

#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

#include "FPSCounter.h"

HWND hwnd = NULL;
bool lbutton_down = false;
int mouse_x = -1;
int mouse_y = -1;
int old_mouse_x = -1;
int old_mouse_y = -1;
float max_diff = 0.0f;

FPSCounter fps;
float max_fps;

void MyDraw(HDC hdc)
{
	HPEN pen, oldpen;
	HBRUSH brush, oldbrush;

	float diff;
	char str[256];
	int dx, dy;

	// prepare pen & brush
	pen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	brush = CreateSolidBrush(RGB(0, 255, 0));

	oldpen = (HPEN)SelectObject(hdc, pen);
	oldbrush = (HBRUSH)SelectObject(hdc, brush);

	// status
	if (lbutton_down) {
		dx = mouse_x - old_mouse_x;
		dy = mouse_y - old_mouse_y;
		diff = (float)sqrt(dx * dx + dy * dy);

		if (max_diff < diff) max_diff = diff;
		if (max_fps < fps.fps()) max_fps = fps.fps();

		sprintf_s(str, 256, "lbutton_down=true");
		TextOut(hdc, 20, 20, str, strlen(str));

		sprintf_s(str, 256, "x=%d, y=%d", mouse_x, mouse_y);
		TextOut(hdc, 20, 40, str, strlen(str));

		sprintf_s(str, 256, "diff=%.2f, max_diff=%.2f", diff, max_diff);
		TextOut(hdc, 20, 60, str, strlen(str));

		sprintf_s(str, 256, "fps=%.2f, max_fps=%.2f", fps.fps(), max_fps);
		TextOut(hdc, 20, 80, str, strlen(str));
	}
	else {
		sprintf_s(str, 256, "lbutton_down=false");
		TextOut(hdc, 20, 20, str, strlen(str));
	}

	// mouse position
	if (lbutton_down) {
		Ellipse(hdc, mouse_x - 50, mouse_y - 50, mouse_x + 50, mouse_y + 50);
	}

	// delete pen & brush
	SelectObject(hdc, oldpen);
	SelectObject(hdc, oldbrush);
	DeleteObject(pen);
	DeleteObject(brush);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message) {
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		MyDraw(hdc);
		EndPaint(hwnd, &ps);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		hwnd = NULL;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
		lbutton_down = true;
		old_mouse_x = GET_X_LPARAM(lParam);
		old_mouse_y = GET_Y_LPARAM(lParam);
		mouse_x = GET_X_LPARAM(lParam);
		mouse_y = GET_Y_LPARAM(lParam);
		fps.clear();
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_LBUTTONUP:
		lbutton_down = false;
		fps.clear();
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_MOUSEMOVE:
		if (lbutton_down) {
			old_mouse_x = mouse_x;
			old_mouse_y = mouse_y;
			mouse_x = GET_X_LPARAM(lParam);
			mouse_y = GET_Y_LPARAM(lParam);
			fps.check();
		}
		else {
			mouse_x = -1;
			mouse_y = -1;
			max_diff = 0;
			max_fps = 0;
		}
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_KEYUP:
		if (wParam == VK_ESCAPE) {
			PostMessage(hwnd, WM_CLOSE, NULL, NULL);
		}
		break;
	case WM_TIMER:
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	MSG msg;

	WNDCLASSEX wc;
	memset(&wc, 0, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	wc.lpszClassName = "dummyclassname";
	RegisterClassEx(&wc);

	hwnd = CreateWindow(wc.lpszClassName, "WM_MOUSEMOVE_test", WS_OVERLAPPEDWINDOW,
		0, 0, 800, 600, NULL, NULL, NULL, NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	SetTimer(hwnd, 0, 1000, NULL);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int) msg.wParam;
}