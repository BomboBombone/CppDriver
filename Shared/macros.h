#pragma once

#define _DEBUG

#ifndef _CLIENT
#ifdef _DEBUG
#define DbgMsg(x, ...) DbgPrintEx(0, 0, x, __VA_ARGS__)

//If DRIVER_TAG is defined then the new overload will allocate pools of tagged memory
//It needs to be written in reverse since debuggers display such tag in little endian, rDyM becomes MyDr(MyDriver)
#else 
#define DbgMsg(x, ...)
#endif
#endif

//Functions

//Make sure to include cpp.h to use this macro
#define ZeroMemory(dst, len) { \
								char* zero_array = (char*) kMalloc(len, NonPagedPool, false); \
								memcpy(dst, zero_array, len); \
								kDelete(zero_array, false); \
							 }

//Constants
#define DRIVER_TAG 'rDyM' 
#define DRIVER_NAME "MyDriv"
#define DRIVER_LNK_NAME "MyDrivLnk"
#define MODULE_TO_FIND L"ntdll.dll"

//Define
#define SIOCTL_TYPE 40000
#define IOCTL_HELLO\
 CTL_CODE( SIOCTL_TYPE, 0x800, METHOD_BUFFERED, FILE_READ_DATA|FILE_WRITE_DATA)
