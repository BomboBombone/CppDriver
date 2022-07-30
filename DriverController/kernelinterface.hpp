#pragma once
#include <stdio.h>
#include "communication.hpp"

class KernelInterface {
public:
	HANDLE hDriver;

	KernelInterface(LPCWSTR RegistryPath) {
		hDriver = CreateFile(RegistryPath, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
	}

	DWORD GetClientAddress() {
		if (hDriver == INVALID_HANDLE_VALUE) {
			std::cout << "Driver handle is invalid: " << GetLastError() << std::endl;
			return 0;
		}
		ULONG Address = 0;
		DWORD Bytes = 0;
		if (DeviceIoControl(hDriver, IO_GET_CLIENT_ADDRESS, &Address, sizeof(Address), &Address, sizeof(Address), &Bytes, NULL)) {
			return Address;
		}
		else {
			std::cout << "Device IO Control failed\n";
		}

		return 0;
	}
};