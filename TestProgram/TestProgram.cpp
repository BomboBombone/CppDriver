
#include <iostream>
#include <Windows.h>
#include <winternl.h>

#pragma comment (lib, "C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.22000.0\\km\\x64\\NtosKrnl.lib")

struct string {
public:
	const char* pBuffer;
	int len;
    //Constructors-Desctructors
    string(const char* pString);
    ~string();
	static string* create(const char* pString);
    //Other functions 
    UNICODE_STRING unicode();
	string* substring(int index);
	string* substring(int index, int length);
    int last_of(char to_find);
};
string::string(const char* pString) {
	len = strlen(pString);
	pBuffer = (char*)malloc((size_t)len + 1);
	strcpy((char*)pBuffer, pString);
}
string* string::create(const char* pString)
{
	auto pNewString = (string*)malloc((size_t)sizeof(string));
	pNewString->len = strlen(pString);
	pNewString->pBuffer = (char*)malloc((size_t)pNewString->len + 1);
	strcpy((char*)pNewString->pBuffer, pString);
	return pNewString;
}
string::~string()
{
	delete((void*)pBuffer);
}

UNICODE_STRING string::unicode()
{
	UNICODE_STRING retValue;
	wchar_t buf[255];
	mbstowcs(buf, (char*)pBuffer, (size_t)len + 1);
	RtlInitUnicodeString(&retValue, buf);
	return retValue;
}

string* string::substring(int index)
{
	char* char_arr = (char*)malloc((size_t)len - index + 1);
	memcpy(char_arr, pBuffer + index, (size_t)len - index);
	char_arr[len - index] = 0;
	string* pRetValue = string::create(char_arr);
	
	delete(char_arr);
	return pRetValue;
}

string* string::substring(int index, int length)
{
	char* char_arr = (char*)malloc((size_t)len - index + 1);
	if (len > index + length) {
		memcpy(char_arr + index, pBuffer, (size_t)len - index);
		char_arr[len - index + 1] = 0;
	}
	else {
		memcpy(char_arr, pBuffer, length);
		char_arr[length + 1] = 0;
	}
	string* pRetValue = string::create(char_arr);
	delete(char_arr);
	return pRetValue;
}

int string::last_of(char to_find)
{
	for (int i = len; i > 0; i--) {
		if (pBuffer[i] == to_find)
			return i;
	}
	return 0;
}

//Length without null terminator
void mbstowcs_p(wchar_t* dst, const char* src, size_t len)
{
    for (size_t i = 0; i < len + 1; i++) {
        *(char*)&dst[i] = src[i];
        *((char*)&dst[i] + 1) = 0x00;
    }
}

void wcstombs_p(char* dst, wchar_t* src, size_t len) {
    for (size_t i = 0; i < len + 1; i++) {
        dst[i] = *(char*)&src[i];
    }
}

UNICODE_STRING GetModuleNameFromPath(PUNICODE_STRING path)
{
    char* char_arr = (char*)malloc((size_t)path->Length + 1);
    wcstombs_p(char_arr, path->Buffer, (size_t)path->Length );
    string full_path(char_arr);
    delete(char_arr);
    int index = full_path.last_of('\\');
    string* modName = full_path.substring(index);
	UNICODE_STRING s;
	PCWSTR wstr = new wchar_t[modName->len + 1];
	mbstowcs_p((wchar_t*)wstr, modName->pBuffer, modName->len);
	RtlInitUnicodeString(&s, wstr);
	return s;
}

int main()
{
	UNICODE_STRING path;
	UNICODE_STRING modName;
	RtlInitUnicodeString(&path, L"\\Device\\Dlls\\mydll.dll");
	RtlInitUnicodeString(&modName, L"CheckString");

	modName = GetModuleNameFromPath(&path);
	wprintf(modName.Buffer);
    return 0;
}