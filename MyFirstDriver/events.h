#pragma once
#pragma comment(lib, "fltMgr.lib")

#include <ntifs.h>
#include <Fltkernel.h>
#include <Shared/macros.h>

#include "utils.h"
#include "data.h"

void ImageLoadCallback(PUNICODE_STRING FullImageName, HANDLE ProcessID, PIMAGE_INFO ImageInfo);