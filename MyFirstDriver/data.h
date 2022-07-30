#pragma once
#include <ntifs.h>
#include <ntdef.h>

typedef struct Globals {
	static ULONGLONG ModuleAddress;
	static PDEVICE_OBJECT pDeviceObject;
	static PUNICODE_STRING dev, dos;

	static void Init();
} globals;
