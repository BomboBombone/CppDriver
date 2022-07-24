#pragma once

#define _DEBUG

#ifndef _CLIENT
#ifdef _DEBUG
#define DbgMsg(x, ...) DbgPrintEx(0, 0, x, __VA_ARGS__)

//If DRIVER_TAG is defined then the new overload will allocate pools of tagged memory
//It needs to be written in reverse since debuggers display such tag in little endian, rDyM becomes MyDr(MyDriver)
#define DRIVER_TAG 'rDyM' 
#else 
#define DbgMsg(x, ...)
#endif
#endif

#define DRIVER_NAME "MyDriv"
#define MODULE_TO_FIND L"ntdll.dll"