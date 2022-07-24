#pragma once
#include "data.h"

ULONGLONG globals::ModuleAddress = 0;
PDEVICE_OBJECT globals::pDeviceObject = nullptr;
PUNICODE_STRING globals::dev = nullptr;
PUNICODE_STRING globals::dos = nullptr;