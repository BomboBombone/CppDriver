#pragma warning (disable : 4047)
#pragma warning (disable : 4302)
#pragma warning (disable : 4311)
#pragma warning (disable : 4100)

#include "events.h"


void ImageLoadCallback(PUNICODE_STRING FullImageName, HANDLE ProcessID, PIMAGE_INFO ImageInfo)
{
	UNICODE_STRING modName = GetModuleNameFromPath(FullImageName);

	//DbgMsg("ImageLoaded: %ls \n", modName.Buffer);

	if (wcsstr(modName.Buffer, MODULE_TO_FIND)) {
		DbgMsg("Module found!\n");

		globals::ModuleAddress = (ULONGLONG)ImageInfo->ImageBase;
		DbgMsg("Process ID: %d \n", (int)ProcessID);
	}

	kDelete(modName.Buffer);
}
