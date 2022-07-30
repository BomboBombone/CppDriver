#pragma once
#include "macros.h"

#define IO_GET_MODULE_ADDRESS CTL_CODE(FILE_DEVICE_UNKNOWN, 0x888, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

template <class T>
struct Message {
	T msg;

	Message(T&& _msg) : msg(_msg) {

	}
};

enum MESSAGE_TYPE {
#ifdef _DEBUG
	TEST
#endif
};