#pragma once
#include <ntifs.h>

#include "cpp.h"

void mbstowcs(wchar_t* dst, char* src, size_t len);
void wcstombs(char* dst, wchar_t* src, size_t len);

//This class supposes it is being initialized from a cstring const char* (for now at least)
struct string {
public:
	int len;
	const char* pBuffer;

	string() = delete;
	//Constructors-Desctructors
	string(const char* pString);
	void Dispose(); //c# style memory free
	static string* create(const char* pString);
	//Other functions 
	UNICODE_STRING unicode();
	string* substring(int index);
	string* substring(int index, int length);
	int last_of(char to_find);
};
