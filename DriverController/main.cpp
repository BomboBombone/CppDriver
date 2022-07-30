
//#include <iostream>
//
//#define _CLIENT
#include <Shared/macros.h>
#include <Shared/message.h>

//
//#include "kernelinterface.hpp"
//
//int main()
//{
//    KernelInterface Driver = KernelInterface(L"\\\\.\\" DRIVER_LNK_NAME);
//
//    ULONG address = Driver.GetClientAddress();
//
//    std::cout << "Module address: " << address << std::endl;
//
//    system("pause");
//}

#include <windows.h>
#include <iostream>

int __cdecl main(int argc, char* argv[])
{
	HANDLE hDevice;
	Message<MESSAGE_TYPE> msg(MESSAGE_TYPE::TEST);
	Message<void*> res(0);
	DWORD dwBytesRead = 0;

	hDevice = CreateFile(L"\\\\.\\" DRIVER_LNK_NAME, GENERIC_WRITE | GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	printf("Handle : %p\n", hDevice);

	DeviceIoControl(hDevice, IO_GET_MODULE_ADDRESS, (LPVOID)&msg, sizeof(msg), &res, sizeof(res), &dwBytesRead, NULL);
	printf("Message received from kerneland : %p\n", res.msg);
	printf("Bytes read : %d\n", dwBytesRead);

	CloseHandle(hDevice);

	system("pause");

	return 0;
}