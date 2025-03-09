CONST FLOAT PI = 3.14159265358979f;
CONST INT w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN);

#include "HUE_FX.h"

DWORD GDI_TIME;

BITMAPINFO CreateBitmapInfo(INT x, INT y) {
	BITMAPINFO bmi = {sizeof(BITMAPINFO), x, y, 1, 32, BI_RGB};
	return bmi;
}

namespace January21 {
	DWORD WINAPI Grayscale(LPVOID lpThreadParam)
	{
		GDI_TIME = 30 * 1000;
		DWORD StopGDI = GetTickCount() + GDI_TIME;
		HDC hdc;
		INT i = 0;
		while (GetTickCount() < StopGDI) {
			hdc = GetDC(0);
			HDC mdc = CreateCompatibleDC(hdc);
			BITMAPINFO bmi = CreateBitmapInfo(w, h);
			RGBQUAD *rgb;
			HSV hsv;
			HBITMAP hbmp = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (HANDLE*)&rgb, NULL, 0);
			SelectObject(mdc, hbmp);
			StretchBlt(mdc, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);
			RGBQUAD rgb2;
			for (INT y = 0; y < h; y++) {
				for (INT x = 0; x < w; x++) {
					INT data = y * w + x;
					rgb2 = rgb[data];
					hsv = rgbQuadToHSV(rgb2);
					hsv.h = fmod(400 + y / h * .02f, 360);
					rgb[data] = hsvToRGB(hsv);
				}
			}
			i++;
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, w, h, SRCCOPY);
			Sleep(10);
			ReleaseDC(NULL, hdc);
		}
	}
}

namespace GDIEffects {
	DWORD WINAPI HypnoticRotation(LPVOID lpThreadParam)
	{
		GDI_TIME = 25 * 1000;
		DWORD StopGDI = GetTickCount() + GDI_TIME;
		HDC hdc;
		FLOAT i = 0;
		while (GetTickCount() < StopGDI) {
			hdc = GetDC(0);
			HDC mdc = CreateCompatibleDC(hdc);
			SelectObject(mdc, CreateCompatibleBitmap(hdc, w, h));
			INT amount = cos(i) * 45;
			RECT rect;
			GetWindowRect(GetDesktopWindow(), &rect);
			POINT point[3] = {
				rect.left + amount, rect.top - amount,
				rect.right + amount, rect.top + amount,
				rect.left - amount, rect.bottom - amount
			};
			PlgBlt(mdc, point, hdc, rect.left, rect.top, w, h, NULL, 0, 0);
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, w, h, NOTSRCCOPY);
			i += PI / 15;
			Sleep(10);
			ReleaseDC(NULL, hdc);
		}
	}
	
	DWORD WINAPI ParallelStretchBlur(LPVOID lpThreadParam)
	{
		GDI_TIME = 25 * 1000;
		DWORD END = GetTickCount() + GDI_TIME;
		HDC hdc;
		FLOAT i = 0;
		while (END > GetTickCount()) {
			hdc = GetDC(0);
			HDC mdc = CreateCompatibleDC(hdc);
			INT x = cos(i) * 50;
			INT y = sin(i) * 50;
			SelectObject(mdc, CreateCompatibleBitmap(hdc, w, h));
			BLENDFUNCTION ftn = {AC_SRC_OVER, 0, 128, 0};
			RECT rect;
			GetWindowRect(GetDesktopWindow(), &rect);
			POINT point[3] = {
				rect.left - x, rect.top,
				rect.right + x, rect.top,
				rect.left, rect.bottom
			};
			i += PI / 16;
			StretchBlt(mdc, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);
			PlgBlt(hdc, point, hdc, rect.left, rect.top, w, h, NULL, 0, 0);
			StretchBlt(hdc, x, y, w, h, hdc, 0, 0, w, h, SRCCOPY);
			GdiAlphaBlend(hdc, 0, 0, w, h, mdc, 0, 0, w, h, ftn);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
	
	DWORD WINAPI MadZooming(LPVOID lpThreadParam)
	{
		GDI_TIME = 30 * 1000;
		DWORD END = GetTickCount() + GDI_TIME;
		HDC hdc;
		INT i = 0;
		while (END > GetTickCount()) {
			hdc = GetDC(0);
			HDC mdc = CreateCompatibleDC(hdc);
			SelectObject(mdc, CreateCompatibleBitmap(hdc, w, h));
			BLENDFUNCTION ftn = {AC_SRC_OVER, 0, 128, 0};
			StretchBlt(mdc, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);
			StretchBlt(hdc, 0, 0, w * i, h * i, hdc, 0, 0, w, h, SRCCOPY);
			GdiAlphaBlend(hdc, 0, 0, w, h, mdc, 0, 0, w, h, ftn);
			i++;
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
}

namespace Shaders {
	DWORD WINAPI RGBLines(LPVOID lpThreadParam)
	{
		GDI_TIME = 30 * 1000;
		DWORD StopGDI = GetTickCount() + GDI_TIME;
		HDC hdc;
		INT i = 0;
		while (GetTickCount() < StopGDI) {
			hdc = GetDC(0);
			HDC mdc = CreateCompatibleDC(hdc);
			INT wx = w / 8, hx = h / 8;
			BITMAPINFO bmi = CreateBitmapInfo(wx, hx);
			RGBQUAD *rgb;
			HBITMAP hbmp = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (HANDLE*)&rgb, NULL, 0);
			SelectObject(mdc, hbmp);
			SelectObject(hdc, CreateSolidBrush(RGB(i, i - 128, i - 256)));
			StretchBlt(mdc, 0, 0, wx, hx, hdc, 0, 0, w, h, PATCOPY | SRCCOPY);
			for (INT y = 0; y < hx; y++) {
				for (INT x = 0; x < wx; x++) {
					INT data = y * wx + x;
					INT cx = x - wx / 2, cy = y - hx / 2;
					INT dx = cx * cx, dy = cy * cy;
					rgb[data].rgbRed += 128 + (128 * sin(x + i / 32));
					rgb[data].rgbGreen += 128 + (128 * tan(y + i / 32));
					rgb[data].rgbBlue += 128 + (128 * sin(sqrt(dx + i) / 64));
				}
			}
			i += 10;
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, wx, hx, PATCOPY | SRCCOPY);
			Sleep(10);
			ReleaseDC(NULL, hdc);
		}
	}
	
	DWORD WINAPI FractalsWithTint(LPVOID lpThreadParam)
	{
		GDI_TIME = 25 * 1000;
		DWORD StopGDI = GetTickCount() + GDI_TIME;
		HDC hdc;
		INT i = 0;
		while (GetTickCount() < StopGDI) {
			hdc = GetDC(0);
			HDC mdc = CreateCompatibleDC(hdc);
			INT wx = w / 8, hx = h / 8;
			BITMAPINFO bmi = CreateBitmapInfo(wx, hx);
			RGBQUAD *rgb;
			HBITMAP hbmp = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (HANDLE*)&rgb, NULL, 0);
			SelectObject(mdc, hbmp);
			StretchBlt(mdc, 0, 0, wx, hx, hdc, 0, 0, w, h, SRCCOPY);
			for (INT y = 0; y < hx; y++) {
				for (INT x = 0; x < wx; x++) {
					INT data = y * wx + x;
					INT fx = (i ^ x) | (i ^ y);
					rgb[data].rgbRed = fx * 32;
					rgb[data].rgbGreen = fx & y;
					rgb[data].rgbBlue = fx ^ x;
				}
			}
			i += 10;
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, wx, hx, SRCCOPY);
			Sleep(10);
			ReleaseDC(NULL, hdc);
		}
	}
	
	DWORD WINAPI SierpinskiFade(LPVOID lpThreadParam)
	{
		GDI_TIME = 20 * 1000;
		DWORD StopGDI = GetTickCount() + GDI_TIME;
		HDC hdc;
		FLOAT i = 0;
		while (GetTickCount() < StopGDI) {
			hdc = GetDC(0);
			HDC mdc = CreateCompatibleDC(hdc);
			INT wx = w / 8, hx = h / 8;
			BITMAPINFO bmi = CreateBitmapInfo(wx, hx);
			RGBQUAD *rgb;
			HBITMAP hbmp = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (HANDLE*)&rgb, NULL, 0);
			SelectObject(mdc, hbmp);
			StretchBlt(mdc, 0, 0, wx, hx, hdc, 0, 0, w, h, SRCCOPY);
			for (INT y = 0; y < hx; y++) {
				for (INT x = 0; x < wx; x++) {
					INT data = y * wx + x;
					INT fx = tan(i) * (x & y);
					INT fx2 = cos(i) * ((x | y) - 128);
					rgb[data].rgbRed = fx;
					rgb[data].rgbGreen = -fx;
					rgb[data].rgbBlue = fx2;
				}
			}
			i += PI / 15;
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, wx, hx, SRCCOPY);
			Sleep(10);
			ReleaseDC(NULL, hdc);
		}
	}
	
	DWORD WINAPI FractalBlend(LPVOID lpThreadParam)
	{
		GDI_TIME = 30 * 1000;
		DWORD StopGDI = GetTickCount() + GDI_TIME;
		HDC hdc;
		FLOAT i = 0;
		INT j = 0;
		while (GetTickCount() < StopGDI) {
			hdc = GetDC(0);
			HDC mdc = CreateCompatibleDC(hdc);
			INT wx = w / 8, hx = h / 8;
			BITMAPINFO bmi = CreateBitmapInfo(wx, hx);
			RGBQUAD *rgb;
			HBITMAP hbmp = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (HANDLE*)&rgb, NULL, 0);
			SelectObject(mdc, hbmp);
			INT x2 = cos(i) * 48, y2 = sin(i) * 48;
			StretchBlt(mdc, x2, y2, wx, hx, hdc, 0, 0, w, h, SRCCOPY);
			for (INT y = 0; y < hx; y++) {
				for (INT x = 0; x < wx; x++) {
					INT data = y * wx + x;
					rgb[data].rgbRed = (x + j | y + j) + x2 + y2;
					rgb[data].rgbGreen = (x - j & y + j) + x2 + y2;
					rgb[data].rgbBlue = ((x ^ j) + y - j) + x2 + y2;
				}
			}
			i += PI / 15;
			j++;
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, wx, hx, SRCCOPY);
			Sleep(10);
			ReleaseDC(NULL, hdc);
		}
	}
	
	DWORD WINAPI GlitchCore(LPVOID lpThreadParam)
	{
		GDI_TIME = 25 * 1000;
		DWORD StopGDI = GetTickCount() + GDI_TIME;
		HDC hdc;
		FLOAT i = 0;
		INT j = 0;
		while (GetTickCount() < StopGDI) {
			hdc = GetDC(0);
			HDC mdc = CreateCompatibleDC(hdc);
			INT wx = w / 8, hx = h / 8;
			BITMAPINFO bmi = CreateBitmapInfo(wx, hx);
			RGBQUAD *rgb;
			HBITMAP hbmp = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (HANDLE*)&rgb, NULL, 0);
			SelectObject(mdc, hbmp);
			INT x2 = cos(i) * 48, y2 = sin(i) * 48;
			StretchBlt(mdc, x2, y2, wx, hx, hdc, 0, 0, w, h, SRCCOPY);
			for (INT y = 0; y < hx; y++) {
				for (INT x = 0; x < wx; x++) {
					INT data = y * wx + x;
					INT x3 = x + x2, y3 = y + y2;
					rgb[data].rgbRed = (x3 & y3) + x;
					rgb[data].rgbGreen = 127 * ((x3 + y3) - x) * x2;
					rgb[data].rgbBlue = x3 ^ y3;
				}
			}
			i += PI / 15;
			j++;
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, wx, hx, SRCINVERT);
			Sleep(10);
			ReleaseDC(NULL, hdc);
		}
	}
	
	DWORD WINAPI CirclesWithPatterns(LPVOID lpThreadParam)
	{
		GDI_TIME = 20 * 1000;
		DWORD StopGDI = GetTickCount() + GDI_TIME;
		HDC hdc;
		FLOAT i = 0;
		INT j = 0;
		while (GetTickCount() < StopGDI) {
			hdc = GetDC(0);
			HDC mdc = CreateCompatibleDC(hdc);
			INT wx = w / 8, hx = h / 8;
			BITMAPINFO bmi = CreateBitmapInfo(wx, hx);
			RGBQUAD *rgb;
			HBITMAP hbmp = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (HANDLE*)&rgb, NULL, 0);
			SelectObject(mdc, hbmp);
			INT x2 = cos(i) * 48, y2 = sin(i) * 48;
			StretchBlt(mdc, x2, y2, wx, hx, hdc, 0, 0, w, h, SRCCOPY);
			for (INT y = 0; y < hx; y++) {
				for (INT x = 0; x < wx; x++) {
					INT data = y * wx + x;
					INT x3 = x + x2, y3 = y + y2;
					rgb[data].rgbRed = (x3 * x3) + (y3 * y3);
					rgb[data].rgbGreen = x * (x3 / 4 + y3 / 7);
					rgb[data].rgbBlue = y;
				}
			}
			i += PI / 15;
			j++;
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, wx, hx, SRCERASE);
			Sleep(10);
			ReleaseDC(NULL, hdc);
		}
	}
	
	DWORD WINAPI GlitchCore2(LPVOID lpThreadParam)
	{
		GDI_TIME = 30 * 1000;
		DWORD StopGDI = GetTickCount() + GDI_TIME;
		HDC hdc;
		while (GetTickCount() < StopGDI) {
			hdc = GetDC(0);
			HDC mdc = CreateCompatibleDC(hdc);
			INT wx = w / 8, hx = h / 8;
			BITMAPINFO bmi = CreateBitmapInfo(wx, hx);
			RGBQUAD *rgb;
			HBITMAP hbmp = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (HANDLE*)&rgb, NULL, 0);
			SelectObject(mdc, hbmp);
			StretchBlt(mdc, 0, 0, wx, hx, hdc, 0, 0, w, h, SRCCOPY);
			for (INT y = 0; y < hx; y++) {
				for (INT x = 0; x < wx; x++) {
					INT data = y * wx + x;
					INT x2 = x * HSL(), y2 = y * HSL();
					rgb[data].rgbRed ^= x2;
					rgb[data].rgbGreen &= y2;
					rgb[data].rgbBlue += x2 + y2;
				}
			}
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, wx, hx, NOTSRCERASE);
			Sleep(10);
			ReleaseDC(NULL, hdc);
		}
	}
	
	DWORD WINAPI Static(LPVOID lpThreadParam)
	{
		HDC hdc;
		while (TRUE) {
			hdc = GetDC(0);
			HDC mdc = CreateCompatibleDC(hdc);
			INT wx = w / 8, hx = h / 8;
			BITMAPINFO bmi = CreateBitmapInfo(wx, hx);
			RGBQUAD *rgb;
			HBITMAP hbmp = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (HANDLE*)&rgb, NULL, 0);
			SelectObject(mdc, hbmp);
			StretchBlt(mdc, 0, 0, wx, hx, hdc, 0, 0, w, h, SRCCOPY);
			for (INT y = 0; y < hx; y++) {
				for (INT x = 0; x < wx; x++) {
					INT data = y * wx + x;
					INT x2 = x * (rand() % 32), y2 = y * (rand() % 32);
					rgb[data].rgbRed = x2 ^ y2;
					rgb[data].rgbGreen = x2 ^ y2;
					rgb[data].rgbBlue = x2 ^ y2;
				}
			}
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, wx, hx, SRCCOPY);
			Sleep(10);
			ReleaseDC(NULL, hdc);
		}
	}
}
