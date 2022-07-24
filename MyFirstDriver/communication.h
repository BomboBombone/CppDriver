#pragma once
#include <ntifs.h>

#include "data.h"

#define IO_GET_CLIENT_ADDRESS CTL_CODE(FILE_DEVICE_UNKNOWN, 0x666, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

NTSTATUS IoControl(PDEVICE_OBJECT DeviceObject, PIRP Irp);
NTSTATUS CloseCall(PDEVICE_OBJECT DeviceObject, PIRP Irp);
NTSTATUS CreateCall(PDEVICE_OBJECT DeviceObject, PIRP Irp);